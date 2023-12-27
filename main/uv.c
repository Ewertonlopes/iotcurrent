#include "uv.h"

uint16_t uv_index_output = 0;

void uv_task()
{
    ESP_LOGI(uvTAG , "Task Started\n");
    while (1) {
        uv_index_output = uv_read();
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void uv_init()
{
    adc_config_t adc_config;

    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 8; 
    ESP_ERROR_CHECK(adc_init(&adc_config));
    ESP_LOGI(uvTAG , "ADC started\n");
    xTaskCreate(uv_task, "UV_task", 1024, NULL, 5, NULL);
}

uint16_t uv_read()
{
    const uint16_t UV_LIMITS[] = {226, 317, 407, 502, 605, 794, 880, 975, 1169};

    uint16_t uv_index = 50;
    uint16_t adc_data[10];

    
    if (ESP_OK == adc_read(&adc_data[0])) 
    {
        uint16_t tension = (uint16_t)(((float)adc_data[0]/1024.0f) * 3300.0f);

        for(int i =0; i<9; i++)
        {
            if(tension < UV_LIMITS[i])
            {
                uv_index = i;
                break;
            }
            if(i == 8) uv_index = 10;
        }

        ESP_LOGI(uvTAG , "ADC READ: %d\r\n", adc_data[0]);
    }
    return uv_index;
}