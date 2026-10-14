#include <Arduino.h>

#include "network/network_handler.h"
#include "sensor/light_sensor.h"

void setup()
{
  Serial.begin(115200);
  network_handler::begin();
}

void loop()
{
}
