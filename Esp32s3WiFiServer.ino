/* For Sync Server */

// #include "Esp32s3WiFiServerSync.h"

// const char *ssid = "S3AccessPoint";
// const char *password = "123456";

// void setup() 
// {
//   Serial.begin(115200);
//   pinMode(LED_PIN, OUTPUT);
//   SetupServer(ssid, password);

//   // Start the client handler thread (core 1 or 0 depending on need)
//   xTaskCreatePinnedToCore(
//     ClientHandlerTask,    // Function to run
//     "ClientHandler",      // Name
//     4096,                 // Stack size
//     NULL,                 // Params
//     1,                    // Priority
//     NULL,                 // Task handle
//     1                     // Core 1 (ESP32S3 has dual cores)
//   );
// }

/* For Async Server */
#include "Esp32s3WiFiServerAsync.h"

const char *ssid = "S3AccessPoint";
const char *password = "123456";

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  SetupAsyncServer();
}

void loop() 
{
  // Free to do real-time control logic, sensor reading, etc.
}
