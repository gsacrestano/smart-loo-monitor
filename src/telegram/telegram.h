/**
 * @file telegram.h
 * @brief Telegram bot messaging and polling interface.
 */

#pragma once

#include "utils/stream_message.h"

namespace telegram
{
    /**
     * @brief Initializes the TLS client for Telegram bot communication in insecure mode.
     * @return Always true.
     */
    bool begin();

    /**
     * @brief Sends a text message to the pre-configured Telegram chat ID.
     * @param[in] str Null-terminated string message to send.
     * @return True if the message was sent successfully, false otherwise.
     */
    bool send_message(const char *str);

    /**
     * @brief Checks whether the polling interval has elapsed to query new bot updates.
     * @return True if enough time has passed since the last check, false otherwise.
     */
    bool should_check_messages();

    /**
     * @brief Polls Telegram for new updates and returns the latest message.
     * @return Populated stream_message struct with valid set to true if a message was received, false otherwise.
     */
    stream_message get_last_message();
} // namespace telegram