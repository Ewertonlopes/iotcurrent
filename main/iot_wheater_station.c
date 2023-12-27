/* Power save Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/*
   this example shows how to use power save mode
   set a router or a AP using the same SSID&PASSWORD as configuration of this example.
   start esp8266 and when it connected to AP it will enter power save mode
*/
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_sleep.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "wifimod.h"

#include "mqttmod.h"

#include "dht11.h"
#include "uv.h"

float temperature = 0.0f;
float humidity = 0.0f;


void app_main(void)
{
   ESP_ERROR_CHECK(nvs_flash_init());

   uv_init();

   //ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
   wifi_init_sta();

   
   //esp_sleep_enable_timer_wakeup(10000000);
   //esp_wifi_stop();
   //esp_power_consumption_info(true);

   esp_mqtt_client_handle_t mclient;
   mclient = mqtt_app_start();
   int msg_id;
   char buffer[6];

   
   while(true)
   {
      sprintf(buffer, "%u", uv_index_output);
      const char *msge2 = buffer;
      msg_id = esp_mqtt_client_publish(mclient, "/outside/metsta/uv", msge2, 0, 1, 0);
      

      vTaskDelay(pdMS_TO_TICKS(1000));
      //printf("Entering Light Sleep Mode\n");
      //esp_light_sleep_start();
      //esp_power_consumption_info(false);
   }
}
