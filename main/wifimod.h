#ifndef WIFIABS_H
#define WIFIABS_H

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"

#include "esp_event.h"
#include "esp_wifi.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"


#define ESP_WIFI_SSID      "brisa-1835136"
#define ESP_WIFI_PASS      "osaxzp72"
#define ESP_MAXIMUM_RETRY  5

static EventGroupHandle_t s_wifi_event_group;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *wifiTAG = "Wifi Connection";

static int s_retry_num = 0;

static void conn_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);
void wifi_init_sta(void);
#endif 