#define NAPT 1000
#define NAPT_PORT 10

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <lwip/napt.h>
#include <lwip/dns.h>
#include "EEPROMHelper.h"
#include "HomePage.h"

EEPROMHelper eepromHelper;
ESP8266WebServer webServer(80);

void setup() {
  eepromHelper.begin();
  pinMode(D4, OUTPUT);
  pinMode(D3, INPUT);

  if (eepromHelper.getSSID() != "") {
    setupExtender(eepromHelper.getSSID(), eepromHelper.getPass(), eepromHelper.getAPSSID(), eepromHelper.getAPPass());
  } else {
    WiFi.softAP("Configuration AP "+(String)ESP.getChipId(), "devserapps");
    webServer.on("/", handleHomePage);
    webServer.on("/submit", handleSubmit);
    webServer.begin();
    unsigned long lastToggleTime = millis();
    while (true) {
      webServer.handleClient();
      if (millis() - lastToggleTime >= 400) {
        digitalWrite(D4, !digitalRead(D4));
        lastToggleTime = millis();
      }
    }
  }
}

unsigned long rstPressStartBeforeTime = 0;

void loop() {
  if (!digitalRead(D3)) {
    if (millis() - rstPressStartBeforeTime >= 5000) {
      eepromHelper.clear();
      delay(50);
      ESP.restart();
    }
  } else {
    rstPressStartBeforeTime = millis();
  }

  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }
}

void setupExtender(String ssid, String pass, String apSSID, String apPass) {
  connectWiFi(ssid, pass);
  auto& server = WiFi.softAPDhcpServer();
  server.setDns(WiFi.dnsIP(0));
  WiFi.softAPConfig(IPAddress(172, 217, 28, 254), IPAddress(172, 217, 28, 254), IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID, apPass);
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  
  if (ret == ERR_OK) {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    if (ret == ERR_OK) {
      digitalWrite(D4, LOW);
    }
  }

  if (ret != ERR_OK) {
    digitalWrite(D4, HIGH);
  }
}

void connectWiFi(String ssid, String pass) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  rstPressStartBeforeTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (digitalRead(D3) == LOW) {
      if (millis() - rstPressStartBeforeTime >= 5000) {
        eepromHelper.clear();
        delay(50);
        ESP.restart();
      }
    } else {
      rstPressStartBeforeTime = millis();
    }
    digitalWrite(D4, !digitalRead(D4));
    delay(100);
  }
}

void handleSubmit() {
  if (webServer.hasArg("ssid") && webServer.hasArg("pass") && webServer.hasArg("ap_ssid") && webServer.hasArg("ap_pass")) {
    eepromHelper.setSSID(webServer.arg("ssid"));
    eepromHelper.setPass(webServer.arg("pass"));
    eepromHelper.setAPSSID(webServer.arg("ap_ssid"));
    eepromHelper.setAPPass(webServer.arg("ap_pass"));
    delay(50);
    ESP.restart();
  }
}

void handleHomePage() {
  String homePage = FPSTR(HOME_PAGE);
  webServer.send(200, "text/html", homePage);
}