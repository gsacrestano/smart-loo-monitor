#include <cstdint>
#include <Arduino.h>

#include "light_sensor.h"

namespace
{
    const uint8_t DIGITAL_PIN = 32;
}

namespace light_sensor
{
    void begin()
    {
        pinMode(DIGITAL_PIN, INPUT);
    }

    bool detects_light()
    {
        uint8_t value = digitalRead(DIGITAL_PIN);
        return value == 0;
    }

}