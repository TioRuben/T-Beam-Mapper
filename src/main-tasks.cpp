#include <Arduino.h>
#include "gps.hpp"
#include "oled.hpp"
#include "lorawan.hpp"
#include "main-tasks.hpp"

void taskMainGPS(void *parameter)
{
  for (;;)
  {
    if (locationValid())
    {
      t_location location = getLocation();
      displayLocation(location.latitude, location.longitude);
      Serial.printf("Lat: %.5f, Lon: %.5f", location.latitude, location.longitude);
      Serial.println("");
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

void taskMainSendPosition(void *parameter)
{
  for (;;)
  {
    if (locationValid())
    {
      displayLora("Sending...");
      t_location location = getLocation();
      sendPosition(location.latitude, location.longitude);
    }
    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

void goToSleep(void)
{
  Serial.println("Going to sleep");
  Serial.flush();
  oledSleep();
  loraWanSleep();
  esp_deep_sleep(60 * 1000 * 1000);
}