#include <Arduino.h>

#define I2C_SDA 21
#define I2C_SCL 22

void initDisplay(void);
void displayLocation(double latitude, double longitude);
void updateDisplay(void);
void displayLora(String msg);
void oledSleep(void);