#include <Arduino.h>

#include "network/network_handler.h"
#include "sensor/light_sensor.h"
#include "mqtt/mqtt_client.h"

void setup()
{
  Serial.begin(115200);
  network_handler::begin();
  light_sensor::begin();
  if (!mqtt_client::begin())
    Serial.println("Errror durig mqtt client startup");
}

void loop()
{
  mqtt_client::loop();

  if (light_sensor::detects_light())
    mqtt_client::publish("Light");
  else
    mqtt_client::publish("Dark");

  delay(5000);
}
