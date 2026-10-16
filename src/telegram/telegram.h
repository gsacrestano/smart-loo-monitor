/**
 * @file telegram.h
 * @brief Telegram bot message notification interface.
 */

#pragma once

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
}  // namespace telegram