#include <Arduino.h>
#include "app.h"
#include "network/network_handler.h"
#include "sensor/light_sensor.h"
// #include "mqtt/mqtt_client.h"
#include "telegram/telegram.h"
#include "utils/date.h"

#define INTERVAL 1 * 60UL * 1000UL

namespace
{
    unsigned long start = 0;
    // Monitor how long the light have been on during the day
    unsigned long time_opened = 0;
    int lastday = -1;

}

namespace app
{
    void begin()
    {
        Serial.begin(115200);
        network_handler::begin();
        light_sensor::begin();
        telegram::begin();
        date::begin();
        lastday = date::get_day_of_the_month();
        // if (!mqtt_client::begin()) Serial.println("Errror durig mqtt client startup");
    }
    
    void loop()
    {
        // mqtt_client::loop();
        if (light_sensor::detects_light())
        {
            if (start == 0)
                start = millis();

            // Chek if INTERVAL has passed
            if ((millis() - start) > INTERVAL)
            {
                telegram::send_message("Light is open from too long!");
                time_opened += INTERVAL;
                start = millis();
            }
        }
        // If the light is on off and has passed < INTERVAL store the time
        else if (start != 0)
        {
            time_opened += millis() - start;
            start = 0;
        }

        if (lastday != date::get_day_of_the_month())
        {
            lastday = date::get_day_of_the_month();
            char msg[256];
            snprintf(msg, sizeof(msg), "Yestrday light have been on for: %lu minutes", time_opened / 60000);
            time_opened = 0;
            telegram::send_message(msg);
        }

        delay(500);
    }
}