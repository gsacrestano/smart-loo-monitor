#include <WiFiManager.h>

#include "network_handler.h"

namespace
{
    WiFiManager wifiManager;

}

namespace network_handler
{
    bool begin()
    {
        return wifiManager.autoConnect();
    }

}