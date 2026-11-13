/**
 * @file date.h
 * @brief NTP time synchronization and date retrieval utilities.
 */

#pragma once

#include <cstdint>

namespace date
{
    /**
     * @brief Initializes time synchronization via NTP and configures the local timezone.
     */
    void begin();

    /**
     * @brief Gets the current day of the month from synchronized time info.
     * @return Day of the month (1-31).
     */
    uint8_t get_day_of_the_month();
} // namespace date