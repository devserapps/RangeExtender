#define SSID_MAX_LENGTH 32
#define PASSWORD_MAX_LENGTH 64
#define AP_SSID_MAX_LENGTH 32
#define AP_PASSWORD_MAX_LENGTH 64

#include <EEPROM.h>

class EEPROMHelper {
private:
  String ssid = "";
  String pass = "";
  String apSSID = "";
  String apPass = "";
public:
  EEPROMHelper() {}

  void begin() {
    EEPROM.begin(512);
  }

  void setSSID(String ssid) {
    uint16_t startIndex = 0;
    uint16_t lastIndex = SSID_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      EEPROM.write(i, ssid[i]);
      delay(10);
    }
    EEPROM.commit();
    this->ssid = ssid;
  }

  void setPass(String pass) {
    uint16_t startIndex = SSID_MAX_LENGTH;
    uint16_t lastIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      EEPROM.write(i, pass[i-startIndex]);
      delay(10);
    }
    EEPROM.commit();
    this->pass = pass;
  }

  void setAPSSID(String ssid) {
    uint16_t startIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH;
    uint16_t lastIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH+AP_SSID_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      EEPROM.write(i, ssid[i-startIndex]);
      delay(10);
    }
    EEPROM.commit();
    this->apSSID = ssid;
  }

  void setAPPass(String pass) {
    uint16_t startIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH+AP_SSID_MAX_LENGTH;
    uint16_t lastIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH+AP_SSID_MAX_LENGTH+AP_PASSWORD_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      EEPROM.write(i, pass[i-startIndex]);
      delay(10);
    }
    EEPROM.commit();
    this->apPass = pass;
  }

  String getSSID() {
    if (ssid != "") { return this->ssid; }

    String ssid = "";
    uint16_t startIndex = 0;
    uint16_t lastIndex = SSID_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      ssid += char(EEPROM.read(i));
    }
    return ssid;
  }

  String getPass() {
    if (pass != "") { return this->pass; }

    String pass = "";
    uint16_t startIndex = SSID_MAX_LENGTH;
    uint16_t lastIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      pass += char(EEPROM.read(i));
    }
    return pass;
  }

  String getAPSSID() {
    if (apSSID != "") { return this->apSSID; }

    String ssid = "";
    uint16_t startIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH;
    uint16_t lastIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH+AP_SSID_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      ssid += char(EEPROM.read(i));
    }
    return ssid;
  }

  String getAPPass() {
    if (apPass != "") { return this->apPass; }

    String pass = "";
    uint16_t startIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH+AP_SSID_MAX_LENGTH;
    uint16_t lastIndex = SSID_MAX_LENGTH+PASSWORD_MAX_LENGTH+AP_SSID_MAX_LENGTH+AP_PASSWORD_MAX_LENGTH-1;
    for (uint16_t i = startIndex; i <= lastIndex; i++) {
      pass += char(EEPROM.read(i));
    }
    return pass;
  }

  void clear() {
    for (uint16_t i = 0; i < 512; i++) {
      EEPROM.write(i, 0);           
      delay(10);
    }
    EEPROM.commit();
  }
};