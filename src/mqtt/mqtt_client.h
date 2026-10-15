/**
 * @file mqtt_client.h
 * @brief Lightweight MQTT client interface.
 */

#pragma once

namespace mqtt_client
{
    /**
     * @brief Configures the MQTT broker connection settings and attempts initial connection.
     * @return True if connected to the MQTT broker, false otherwise.
     */
    bool begin();

    /**
     * @brief Maintains the MQTT connection and processes incoming messages. Must be called periodically.
     * @return True if connected and loop executed successfully, false otherwise.
     */
    bool loop();

    /**
     * @brief Publishes a payload string to the pre-configured MQTT topic.
     * @param[in] str Null-terminated string payload to publish.
     * @return True if publication succeeded, false otherwise.
     */
    bool publish(const char *str);
} // namespace mqtt_client