#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <SPIFFS.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
#define BTN_UP     13
#define BTN_DOWN   14
#define BTN_SELECT 25
#define RED_LED    32
#define BLUE_LED   33

String menu[] = {"Start Server", "Restart"};
int menuIndex = 0;
WebServer server(80);
DNSServer dns;
bool serverRunning = false;

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  for (int i = 0; i < 2; i++) {
    display.setCursor(0, i * 16);
    display.print((i == menuIndex) ? "> " : "  ");
    display.print(menu[i]);
  }
  display.display();
}

void startServer() {
  if (!SPIFFS.begin(true)) return;
  WiFi.softAP("arian-portfolio", "", 1, 0, 4);
  dns.start(53, "*", WiFi.softAPIP());
  server.serveStatic("/resume.jpg", SPIFFS, "/resume.jpg");
  server.onNotFound([]() {
    server.send(200, "text/html", "<img src='/resume.jpg' style='width:100%'>");
  });
  server.begin();
  serverRunning = true;
  digitalWrite(RED_LED, HIGH);
}

void restartDevice() {
  ESP.restart();
}

void handleInput() {
  if (digitalRead(BTN_UP) == LOW) { menuIndex = (menuIndex - 1 + 2) % 2; drawMenu(); delay(200); }
  if (digitalRead(BTN_DOWN) == LOW) { menuIndex = (menuIndex + 1) % 2; drawMenu(); delay(200); }
  if (digitalRead(BTN_SELECT) == LOW) {
    if (menu[menuIndex] == "Start Server" && !serverRunning) startServer();
    else if (menu[menuIndex] == "Restart") restartDevice();
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT); pinMode(BLUE_LED, OUTPUT);
  pinMode(BTN_UP, INPUT_PULLUP); pinMode(BTN_DOWN, INPUT_PULLUP); pinMode(BTN_SELECT, INPUT_PULLUP);
  digitalWrite(RED_LED, LOW); digitalWrite(BLUE_LED, HIGH);
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); display.setTextSize(1); display.setTextColor(WHITE);
  display.setCursor(0, 0); display.println("ESP32 Resume Server"); display.display(); delay(1000);
  drawMenu();
}

void loop() {
  handleInput();
  if (serverRunning) {
    dns.processNextRequest();
    server.handleClient();
  }
}
