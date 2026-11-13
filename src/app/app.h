/**
 * @file app.h
 * @brief Core application lifecycle management and monitoring loop.
 */

#pragma once

namespace app
{
    /**
     * @brief Initializes system peripherals, network connection, sensors, and communication clients.
     */
    void begin();

    /**
     * @brief Main execution loop that monitors sensor states, tracks elapsed time, and handles notifications.
     */
    void loop();
} // namespace app