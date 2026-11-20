#include "Arduino.h"

#include "event_handler.h"
#include "../light/light_manager.h"
#include "telegram/telegram.h"

namespace event_handler
{

    void handle_event(const char *event)
    {
        char log[256];

        snprintf(log, sizeof(log), "\n%s - %d\n", event,  strlen(event));
        Serial.print(log);
        

        if (strncmp(event, "Time", strlen("Time")) == 0)
        {
            char msg[256];
            snprintf(msg, sizeof(msg), "Time: %ld", light_manager::manage_time_opened(false));
            telegram::send_message(msg);
        }
    }
}