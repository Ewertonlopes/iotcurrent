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

#include "curr.h"

void makefloat(float number, char* buffer)
{
   int16_t number_n = (uint16_t)(number);
   uint16_t number_v = 0;
   if(number > 0)
   {
      number_v = (uint16_t)(number*1000.0f - (float)number_n*1000.0f);
      if(number_v<100)
      {
         if(number_v<10)
         {
            sprintf(buffer, "%u.00%u", number_n,number_v);
         }
         else
         {
            sprintf(buffer, "%u.0%u", number_n,number_v);
         }   
      }
      else
      {
         sprintf(buffer, "%u.%u", number_n,number_v);  
      }
   }
   else
   {
      number_v = (uint16_t)((float)number_n*1000.0f - number*1000.0f);
      if(number_v<100)
      {
         if(number_v<10)
         {
            sprintf(buffer, "-%u.00%u", number_n,number_v);
         }
         else
         {
            sprintf(buffer, "-%u.0%u", number_n,number_v);
         }
      }
      else
      {
         sprintf(buffer, "-%u.%u", number_n,number_v);  
      }
   }
}

static const char *mTAG = "Main";

void app_main(void)
{
   ESP_ERROR_CHECK(nvs_flash_init());
   
   //ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
   wifi_init_sta();
   
   curr_init();

   //esp_sleep_enable_timer_wakeup(10000000);
   //esp_wifi_stop();
   //esp_power_consumption_info(true);

   esp_mqtt_client_handle_t mclient;
   mclient = mqtt_app_start();
   int msg_id;
   char buffer[8];
   char pbuffer[8];


   while(true)
   {
      float current = max_current*0.707;
      makefloat(current,buffer);
      float potency = current*220;
      makefloat(potency,pbuffer);

      const char *msge = buffer;
      msg_id = esp_mqtt_client_publish(mclient, "/inside/table/current", msge, 0, 1, 0);

      const char *msge2 = pbuffer;
      msg_id = esp_mqtt_client_publish(mclient, "/inside/table/potency", msge2, 0, 1, 0);

      // ESP_LOGI(mTAG, "Corrente: %s",buffer);
      // ESP_LOGI(mTAG, "Potencia: %s",pbuffer);
      
      vTaskDelay(pdMS_TO_TICKS(1000));
      //printf("Entering Light Sleep Mode\n");
      //esp_light_sleep_start();
      //esp_power_consumption_info(false);
   }
}
