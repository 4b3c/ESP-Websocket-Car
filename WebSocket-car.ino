#include <WiFi.h>
#include "driving.h"
#include "websocket.h"
#include "html.h"


// Network credentials
const char* ssid = "ABRAMS-PC-2020";
const char* password = "googlyeyes";

void setup() {
  Serial.begin(115200);

  initDrive();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
ww
  initWebsocket();
}


void loop() {
  // Nothing to do here
}
