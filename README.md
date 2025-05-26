# 🖥️ ESP32 Resume Server (Captive Portal + OLED + Buttons)

This project creates a free offline Wi-Fi hotspot (`arian-portfolio`) hosted on an ESP32.
- When a user connects, they see a captive portal with a fullscreen image of your resume.
- An OLED screen shows a simple button-controlled UI menu.
- Two LEDs show power and server status.

## 📁 Folder Structure

```
esp32-resume-server/
├── resume_server.ino
├── data/
│   └── resume.jpg
```

## 🧠 Features
- OLED menu to start server or restart
- UP/DOWN/SELECT navigation via buttons
- SPIFFS-based resume hosting (`/resume.jpg`)
- Blue LED (GPIO 33): always on when powered
- Red LED (GPIO 32): on when server is active

## 🛠 Wiring

| Component    | ESP32 Pin |
|--------------|------------|
| OLED SDA     | D21        |
| OLED SCL     | D22        |
| Button UP    | D13        |
| Button DOWN  | D14        |
| Button SELECT| D25        |
| Red LED      | D32        |
| Blue LED     | D33        |

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| GND      | GND       |
| VCC      | 3.3V      |
| SCL      | GPIO 22   |
| SDA      | GPIO 21   |

🟦 Blue LED (Power Indicator)
Anode (long leg) → GPIO 33
Cathode (short leg) → GND
Optional: add a 330Ω resistor in series with the anode

🟥 Red LED (Server Status)
Anode → GPIO 32
Cathode → GND
Optional: 330Ω resistor in series.

🔘 Buttons (Pull-up style)
Each button is connected as:
-One leg to GND
-Other leg to:

|Button	   | GPIO Pin  |
| -------- | --------- |
|   UP	   |  GPIO 13  |
|  DOWN	   |  GPIO 14  |
|  SELECT  |	GPIO 25  |

## 📸 Usage
- Place your `resume.jpg` inside the `/data` folder
- Upload it using **ESP32 Sketch Data Upload** in Arduino IDE 1.8.19
