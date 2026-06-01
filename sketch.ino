#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);

const int ledPin = 2;

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <style>
    body {
      font-family: Arial;
      text-align: center;
      margin-top: 50px;
    }
    button {
      width: 120px;
      height: 50px;
      font-size: 18px;
      margin: 10px;
    }
  </style>
</head>
<body>
  <h1>ESP32 Web Server</h1>
  <h2>LED Control</h2>

  <a href="/on">
    <button>LED ON</button>
  </a>

  <a href="/off">
    <button>LED OFF</button>
  </a>

</body>
</html>
)rawliteral";

  Serial.println("Home Page Opened");
  server.send(200, "text/html", html);
}

void ledOn() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  server.sendHeader("Location", "/");
  server.send(303);
}

void ledOff() {
  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", ledOn);
  server.on("/off", ledOff);

  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
