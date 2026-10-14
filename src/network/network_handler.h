/**
 * @file network_handler.h
 * @brief Automatic Wi-Fi connection and configuration management.
 */

#pragma once

#include <cstddef>

namespace network_handler
{
    /**
     * @brief Connects to a saved Wi-Fi network or starts a portal to configure credentials.
     * @return True if connected successfully to Wi-Fi, false otherwise.
     */
    bool begin();
}  // namespace network_handler