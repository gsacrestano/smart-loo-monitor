#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#include "telegram.h"

#define INTERVAL 0.5 * 6UL * 1000UL

namespace
{
    WiFiClientSecure client;
    UniversalTelegramBot bot(BOT_TOKEN, client);
    unsigned long last_notify = 0;


}

namespace telegram
{
    bool begin()
    {
        client.setInsecure();
        return true;
    }
    bool send_message(const char *str)
    {
        if (str != nullptr)
            return bot.sendMessage(CHAT_ID, str);
        return false;
    }

    bool should_check_messages(){

        unsigned long now = millis();
        if(now - last_notify > INTERVAL){
            last_notify = now;
            return true;
        }
        return false;


    }
    stream_message get_last_message()
    {

        stream_message msg;
        int last_msg = bot.getUpdates(bot.last_message_received + 1);

        if(last_msg <= 0)
            return msg;

        msg.message = bot.messages[last_msg - 1].text;
        msg.sender = bot.messages[last_msg - 1].from_name;
        msg.valid = true;

        return msg;
    }

}