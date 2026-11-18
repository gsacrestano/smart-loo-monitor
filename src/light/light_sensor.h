/**
 * @file light_sensor.h
 * @brief Digital light sensor interface.
 */

#pragma once

namespace light_sensor
{
    /**
     * @brief Configures the digital pin mode for the light sensor.
     */
    void begin();

    /**
     * @brief Checks if light is detected by the sensor.
     * @return True if light is detected (pin reads LOW), false otherwise.
     */
    bool detects_light();
} // namespace light_sensor