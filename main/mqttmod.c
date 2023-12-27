#include "mqttmod.h"

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(mqttTAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_publish(client, "/outside/metsta/humi", "75", 0, 1, 0);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(mqttTAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(mqttTAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            break;
        case MQTT_EVENT_ERROR:
            break;
        default:
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) 
{
    ESP_LOGD(mqttTAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

esp_mqtt_client_handle_t  mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = 
    {
        .uri = "mqtt://192.168.0.2",
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
    return client;
}