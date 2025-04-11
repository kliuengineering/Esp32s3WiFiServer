#ifndef __ESP32S3WIFISERVERSYNC_H__
#define __ESP32S3WIFISERVERSYNC_H__

#include <WiFi.h>

#define LED_PIN LED_BUILTIN
extern const char *ssid;
extern const char *password;

WiFiServer server(80);

// Setup Access Point and start server
void SetupServer(const char *SSID, const char *PASSWORD)
{
  WiFi.softAP(SSID, PASSWORD);
  delay(1000);
  Serial.println("Access Point Started.");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void ClientHandlerTask(void *parameter)
{
  for (;;)
  {
    WiFiClient client = server.available();

    if (client)
    {
      Serial.println("New Client.");
      String currentLine = "";
      unsigned long connectionStart = millis();

      while (client.connected())
      {
        // Timeout if client hangs too long
        if (millis() - connectionStart > 5000) {
          Serial.println("Client timed out.");
          break;
        }

        if (client.available())
        {
          char c = client.read();
          Serial.write(c);

          if (c == '\n')
          {
            if (currentLine.length() == 0)
            {
              // Send minimal HTML response
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");
              client.println();

              client.println("<html><body>");
              client.print("<a href=\"/H\">LED ON</a><br>");
              client.print("<a href=\"/L\">LED OFF</a><br>");
              client.println("</body></html>");
              break;
            }
            else
            {
              currentLine = "";
            }
          }
          else if (c != '\r')
          {
            currentLine += c;
          }

          // Set LED state
          if (currentLine.endsWith("GET /H"))
          {
            digitalWrite(LED_PIN, LOW);
          }
          if (currentLine.endsWith("GET /L"))
          {
            digitalWrite(LED_PIN, HIGH);
          }

          // Reset timeout timer on activity
          connectionStart = millis();
        }

        // Prevent watchdog reset
        vTaskDelay(1);
      }

      client.stop();
      Serial.println("Client Disconnected.");
    }

    // Prevent CPU hogging
    vTaskDelay(10);
  }
}

#endif
