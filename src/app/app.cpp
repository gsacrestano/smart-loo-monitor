#include <Arduino.h>
#include "app.h"
#include "network/network_handler.h"
#include "telegram/telegram.h"
#include "light/light_manager.h"
#include "event_handler.h"

namespace app
{
    void begin()
    {
        network_handler::begin();
        telegram::begin();
        light_manager::begin();
        Serial.print("\nApp started\n");
    }

    void loop()
    {
        // mqtt_client::loop();

        if (telegram::should_check_messages())
        {
            stream_message msg = telegram::get_last_message();
            if (msg.valid)
                event_handler::handle_event(msg.message.c_str());
        }

        if (light_manager::should_send_alert())
            telegram::send_message("Light is open from too long!");

        if (light_manager::should_send_daily_recap())
        {
            char msg[256];
            snprintf(msg, sizeof(msg), "Yesterday light have been on for: %ld minutes", light_manager::manage_time_opened(true));
            telegram::send_message(msg);
        }

        delay(500);
    }
}