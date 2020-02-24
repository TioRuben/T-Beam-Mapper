#include <Arduino.h>

typedef struct
{
  double latitude;
  double longitude;
} t_location;

void initGPS(void);
void taskUpdateGPS(void *parameter);
bool locationValid(void);
t_location getLocation(void);