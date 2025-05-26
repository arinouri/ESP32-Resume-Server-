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

## 📸 Usage
- Place your `resume.jpg` inside the `/data` folder
- Upload it using **ESP32 Sketch Data Upload** in Arduino IDE 1.8.19
