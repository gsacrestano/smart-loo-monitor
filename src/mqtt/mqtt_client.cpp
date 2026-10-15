#include <WiFi.h>
#include <PubSubClient.h>

#include "mqtt_client.h"

namespace
{
    const char *client_id = "esp32-client";
    const char *mqtt_broker = "10.92.79.191";
    const char *topic = "smart-loo-monitor/light";
    const int mqtt_port = 1883;
    WiFiClient espClient;
    PubSubClient client(espClient);

    void callback(char *topic, byte *payload, unsigned int length) {}
    void try_connection()
    {
        uint8_t counter = 0;
        while (!client.connected() && counter < 10)
        {
            Serial.printf("The client %s connects to the public MQTT broker\n", client_id);
            if (client.connect(client_id))
            {
                Serial.println("Connected");
                break;
            }
            else
            {
                Serial.print("failed with state ");
                Serial.print(client.state());
                counter++;
                delay(2000);
            }
        }
    }
}

namespace mqtt_client
{
    bool begin()
    {
        if (WiFi.status() != WL_CONNECTED)
            return false;

        client.setServer(mqtt_broker, mqtt_port);
        client.setCallback(callback);
        try_connection();
        return client.connected();
    }
    bool loop()
    {
        if (!client.connected())
        {
            try_connection();
            if (!client.connected())
                return false;
        }

        return client.loop();
    }
    bool publish(const char *str)
    {
        if (!client.connected())
        {
            Serial.println("Client not connected");
            return false;
        }
        if (str == nullptr)
            return false;

        return client.publish(topic, str);
    }
} // namespace mqtt_client
