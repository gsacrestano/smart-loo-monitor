#include <Arduino.h>

#include "network/network_handler.h"
#include "sensor/light_sensor.h"

void setup()
{
  Serial.begin(115200);
  network_handler::begin();
  light_sensor::begin();
}

void loop()
{
  if (light_sensor::detects_light())
    Serial.print("Light");
  else
    Serial.print("Dark");

  delay(5000);
}
