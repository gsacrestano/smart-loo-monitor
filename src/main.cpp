#include <Arduino.h>
#include "app/app.h"


void setup()
{
  Serial.begin(115200);
  app::begin();
}

void loop()
{
  app::loop();
}
