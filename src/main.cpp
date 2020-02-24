#include <Arduino.h>
#include <Wifi.h>
#include "gps.hpp"
#include "oled.hpp"
#include "lorawan.hpp"
#include "main-tasks.hpp"

void setup()
{
  Serial.begin(115200);
  btStop();
  WiFi.mode(WIFI_MODE_NULL);
  initGPS();
  initDisplay();
  initLora();
  xTaskCreate(taskMainGPS, "taskMainGPS", 5000, NULL, 5, NULL);
  xTaskCreate(taskMainSendPosition, "taskMainSendPosition", 15000, NULL, 5, NULL);
}

void loop()
{
  loraLoop();
}
