#include <Wire.h>
#include <SSD1306Wire.h>
#include <OLEDDisplayUi.h>
#include "oled.hpp"

SSD1306Wire display(0x3c, I2C_SDA, I2C_SCL);
String latitudeStr = "", longitudeStr = "", loraStr = "";

void initDisplay(void)
{
  if (!display.init())
  {
    Serial.println("Error initializing display");
  }
  else
  {
    display.displayOn();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, "Initializing...");
    display.display();
  }
}

void displayLocation(double latitude, double longitude)
{
  latitudeStr = String("Latitude: " + String(latitude, 5));
  longitudeStr = String("Longitude: " + String(longitude, 5));
  updateDisplay();
}

void displayLora(String msg)
{
  loraStr = String("LoRa: " + msg);
  updateDisplay();
}

void updateDisplay(void)
{
  display.clear();
  display.display();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, latitudeStr);
  display.drawString(0, 18, longitudeStr);
  display.drawString(0, 45, loraStr);
  display.display();
}

void oledSleep(void)
{
  display.clear();
  display.display();
  display.displayOff();
}