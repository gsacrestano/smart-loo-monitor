/**
 * @file stream_message.h
 * @brief Incoming message payload structure for stream polling.
 */

#pragma once

#include <Arduino.h>

/**
 * @brief Represents a message received from a messaging stream.
 */
struct stream_message
{
    String message;    ///< Message text content.
    String sender;     ///< Sender display name.
    bool valid = false; ///< True if the struct contains a valid received message.
};