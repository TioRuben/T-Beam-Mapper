#include <TinyGPS++.h>
#include "gps.hpp"

TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

void initGPS(void)
{
  SerialGPS.begin(9600, SERIAL_8N1, 12, 15); //17-TX 18-RX
  xTaskCreate(taskUpdateGPS, "taskUpdateGPS", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
}

void taskUpdateGPS(void *parameter)
{
  for (;;)
  {
    while (SerialGPS.available())
    {
      gps.encode(SerialGPS.read());
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

bool locationValid(void)
{
  return gps.location.lat() != 0 && gps.location.lng() != 0;
}

t_location getLocation(void)
{
  return {
      gps.location.lat(),
      gps.location.lng()};
}