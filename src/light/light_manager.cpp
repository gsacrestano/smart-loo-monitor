#include "light_sensor.h"
#include "light_sensor.h"
#include "../utils/date.h"
#include <Arduino.h>

#define INTERVAL 1 * 60UL * 1000UL

namespace
{
    unsigned long start = 0;
    // Monitor how long the light have been on during the day
    unsigned long time_opened = 0;
    int lastday;
}

namespace light_manager
{
    void begin()
    {
        light_sensor::begin();
        date::begin();
        lastday = date::get_day_of_the_month();

        Serial.print("\nLight Manager started\n");
    }

    bool should_send_alert()
    {
        if (light_sensor::detects_light())
        {
            if (start == 0)
                start = millis();

            // Chek if INTERVAL has passed
            if ((millis() - start) > INTERVAL)
            {
                time_opened += INTERVAL;
                start = millis();
                return true;
            }
        }
        // If the light is on off and has passed < INTERVAL store the time
        else if (start != 0)
        {
            time_opened += millis() - start;
            start = 0;
        }
        return false;
    }

    bool should_send_daily_recap()
    {
        int today = date::get_day_of_the_month();
        if (lastday != today)
        {
            lastday = today;
            return true;
        }
        return false;
    }

    unsigned long manage_time_opened(bool reset)
    {
        unsigned long temp = time_opened;
        if (reset == true)
            time_opened = 0;
        return temp/60000UL;
    }

} // namespace light_manager
