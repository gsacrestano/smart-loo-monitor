#include <Arduino.h>

#include "network/network_handler.h"
#include "sensor/light_sensor.h"
#include "mqtt/mqtt_client.h"
#include "telegram/telegram.h"

#define INTERVAL 15
unsigned long start = 0;

void setup()
{
  Serial.begin(115200);
  network_handler::begin();
  light_sensor::begin();
  telegram::begin();
  // if (!mqtt_client::begin()) Serial.println("Errror durig mqtt client startup");
}

void loop()
{
  // mqtt_client::loop();
  if (light_sensor::detects_light())
  {
    if (start == 0)
      start = millis();

    if ((millis() - start) > (INTERVAL * 60UL * 1000UL))
    {
      if (telegram::send_message("Light is open from too long!"))
        start = millis();
    }
  }
  else if (start != 0)
    start = 0;

  delay(500);
}
