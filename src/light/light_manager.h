/**
 * @file light_manager.h
 * @brief Light state monitoring, duration tracking, and daily recap scheduling.
 */

#pragma once

#include <cstdint>

namespace light_manager
{
    /**
     * @brief Initializes the light sensor, date synchronization, and initial day marker.
     */
    void begin();

    /**
     * @brief Evaluates whether an alert should be sent based on how long the light has stayed on.
     * @return True if the alert interval has elapsed, false otherwise.
     */
    bool should_send_alert();

    /**
     * @brief Checks if a new day has started to trigger a daily recap notification.
     * @return True if the date has changed since the last check, false otherwise.
     */
    bool should_send_daily_recap();

    /**
     * @brief Retrieves the total accumulated time the light has been open in minutes.
     * @param[in] reset If true, resets the accumulated time counter to zero.
     * @return Total elapsed time in minutes.
     */
    unsigned long manage_time_opened(bool reset);

} // namespace light_manager