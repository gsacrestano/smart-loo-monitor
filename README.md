# Smart Loo Monitor

`smart-loo-monitor` is an embedded IoT project built using the Arduino framework (PlatformIO target). It solves a practical everyday problem: preventing energy waste caused by accidentally leaving the bathroom light turned on for extended periods. 

The device monitors ambient light levels using a digital light sensor and measures how long the light remains active. If the light stays on past a defined threshold, an automated alert notification is transmitted. At the of the day it sends a recap of the day.

In addition to serving its primary practical function, this project serves as an experimental setup for testing digital optical sensors and exploring embedded communication protocols, specifically Telegram Bot API integration and MQTT messaging.

---

## Features

- **Light Detection**: Continuously samples input from a digital light sensor connected to GPIO pin 32.
- **Timer & Threshold Monitoring**: Tracks duration while light is active (default threshold set to 15 minutes).
- **Telegram Notifications**: Automatically triggers a Telegram message to a designated user/group when the threshold is exceeded.
- **Network Management**: Integrated Wi-Fi/Network handling via `network_handler`.
- **MQTT Capabilities**: Includes built-in support for MQTT protocol publishing and subscription (commented out in the default workflow in favor of direct Telegram notifications, but fully implemented and operational).

---

## Hardware Requirements

- **Microcontroller**: ESP32 or compatible Arduino-supported board with Wi-Fi functionality.
- **Sensor**: Digital Light/Photosensitive Sensor Module (connected to Pin `32`).
- Power source and connection cables.

---

## Setup & Configuration

This project is configured for building with **PlatformIO**.

### 1. Environment Variables

To prevent committing sensitive authorization keys to source control, the project expects Telegram credentials to be injected during compilation using build flags.

Define the following environment variables on your host system:

- `BOT_TOKEN`: The API key provided by Telegram's `@BotFather`.
- `CHAT_ID`: The unique target user or channel ID for receiving alerts.

### 2. PlatformIO Configuration (`platformio.ini`)

Ensure your `platformio.ini` file includes the corresponding `build_flags` mapping to system environment variables:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

build_flags = 
    -D BOT_TOKEN=\"${sysenv.BOT_TOKEN}\"
    -D CHAT_ID=\"${sysenv.CHAT_ID}\"
```

---

## Code Overview & Architecture

### Application Flow (`app.cpp`)

The main routine manages the state machine for timing and alert dispatching:

```cpp
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
```

### Protocol Usage: Telegram vs MQTT

- **Telegram**: Used as the default primary alert delivery mechanism for direct real-time mobile notifications.
- **MQTT**: The repository includes a complete MQTT driver (`mqtt/mqtt_client.h`). While currently commented out in `main.cpp` for runtime convenience, the code is fully implemented and can be easily re-enabled for integration with home automation platforms like Home Assistant or Node-RED.

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.
