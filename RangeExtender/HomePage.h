const char HOME_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Wi-Fi Range Extender Configuration</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f4f4f9;
        }
        .container {
            width: 320px;
            padding: 20px;
            background-color: #ffffff;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            text-align: center;
        }
        .container h2 {
            margin-bottom: 20px;
            color: #333;
        }
        .form-field {
            margin-bottom: 15px;
            text-align: left;
            display: flex;
            flex-direction: column;
            align-items: flex-start;
            width: 100%;
        }
        .form-field label {
            font-size: 14px;
            color: #666;
            margin-bottom: 5px;
            width: 100%;
        }
        .form-field input {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
            font-size: 14px;
        }
        .submit-button {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 16px;
            cursor: pointer;
            margin-top: 10px;
        }
        .submit-button:hover {
            background-color: #45a049;
        }
        .error-message {
            color: red;
            font-size: 14px;
            margin-top: 10px;
            display: none;
        }
    </style>
</head>
<body>

<div class="container" id="container">
    <h2>Wi-Fi Range Extender Configuration</h2>
    <form id="extenderForm">
        <div class="form-field">
            <label for="ssid">SSID</label>
            <input type="text" id="ssid" name="ssid" required>
        </div>
        <div class="form-field">
            <label for="pass">Password</label>
            <input type="password" id="pass" name="pass" required>
        </div>
        <div class="form-field">
            <label for="ap_ssid">AP SSID</label>
            <input type="text" id="ap_ssid" name="ap_ssid" required>
        </div>
        <div class="form-field">
            <label for="ap_pass">AP Password</label>
            <input type="password" id="ap_pass" name="ap_pass" required>
        </div>
        <button type="button" class="submit-button" onclick="submitSettings()">Submit</button>
        <p class="error-message" id="errorMessage">Error: Missing parameters.</p>
    </form>
</div>

<script>
    function submitSettings() {
        const ssid = document.getElementById("ssid").value;
        const pass = document.getElementById("pass").value;
        const apSSID = document.getElementById("ap_ssid").value;
        const apPass = document.getElementById("ap_pass").value;

        if (ssid && pass && apSSID && apPass) {
            const url = `/submit?ssid=${encodeURIComponent(ssid)}&pass=${encodeURIComponent(pass)}&ap_ssid=${encodeURIComponent(apSSID)}&ap_pass=${encodeURIComponent(apPass)}`;
            const request = new XMLHttpRequest();
            request.open("GET", url, true);
            request.onreadystatechange = null;
            document.getElementById("container").innerHTML = "<h2>Blinking every 0.1 seconds means connecting to Wi-Fi</h2><h3>Blinking every 0.4 seconds is configuration required</h3><h3>Hold flash button for about 5 seconds to reset</h3>";
            request.send();
        } else {
            document.getElementById("errorMessage").style.display = "block";
        }
    }
</script>

</body>
</html>
)=====";