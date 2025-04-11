#ifndef __ESP32S3WIFISERVERASYNC_H__
#define __ESP32S3WIFISERVERASYNC_H__

// install ESP Async WebServer by ESP32Async, version 3.7.6
// install Async TCP by ESP32Async, version 3.3.8

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define LED_PIN LED_BUILTIN

extern const char *ssid;
extern const char *password;

AsyncWebServer server(80);

// Setup access point and start async server
void SetupAsyncServer()
{
  WiFi.softAP(ssid, password);
  delay(500);  // give some time to stabilize

  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Root page
  server.on (
    "/", 
    HTTP_GET, 
    [] (AsyncWebServerRequest *request) 
    {
      String html = "<html><body>"
                    "<h3>ESP32S3 LED Control</h3>"
                    "<a href=\"/H\">Turn LED OFF</a><br>"
                    "<a href=\"/L\">Turn LED ON</a><br>"
                    "</body></html>";
      request->send(200, "text/html", html);
    }
  );

  // Turn ON LED
  server.on (
    "/H", 
    HTTP_GET, 
    [] (AsyncWebServerRequest *request) 
    {
      digitalWrite(LED_PIN, HIGH);
      request->redirect("/");
    }
  );

  // Turn OFF LED
  server.on (
    "/L", 
    HTTP_GET, 
    [] (AsyncWebServerRequest *request) 
    {
      digitalWrite(LED_PIN, LOW);
      request->redirect("/");
    }
  );

  server.begin();
}

#endif