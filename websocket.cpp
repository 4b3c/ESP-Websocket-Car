#include <ESPAsyncWebServer.h>
#include <pgmspace.h>
#include "driving.h"
#include "html.h"

// Create an instance of the server
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Handle input coming from the webserver
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  } else if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->opcode == WS_TEXT) {
      data[len] = 0;
      String message = (char *)data;
      Serial.print("Message received: ");
      Serial.println(message);

      if (message.startsWith("speed:")) {
        int speed = message.substring(6).toInt();
        drive(speed);
      } else if (message.startsWith("steering:")) {
        int steering = message.substring(9).toInt();
        steer(steering);
      }
    }
  }
}

// Setup WebSocket
void initWebsocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);

  // Serve static HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", htmlContent);
  });

  server.begin();
}
