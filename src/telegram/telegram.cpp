#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#include "telegram.h"

namespace
{
    WiFiClientSecure client;
    UniversalTelegramBot bot(BOT_TOKEN, client);

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

}