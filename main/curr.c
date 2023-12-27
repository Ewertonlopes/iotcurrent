#include "curr.h"

double curr_index_output = 0;

void curr_task()
{
    ESP_LOGI(currTAG , "Task Started\n");
    while (1) {
        curr_index_output = curr_read();
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void curr_init()
{
    adc_config_t adc_config;

    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 8; 
    ESP_ERROR_CHECK(adc_init(&adc_config));
    ESP_LOGI(currTAG , "ADC started\n");
    xTaskCreate(curr_task, "curr_task", 1024, NULL, 5, NULL);
}

double curr_read()
{
    uint16_t adc_data[10];
    uint16_t tension;
    
    if (ESP_OK == adc_read(&adc_data[0])) 
    {
        uint16_t tension = (uint16_t)(((float)adc_data[0]/1024.0f) * 3300.0f);

        double current = 0.000001515*(tension - 1.65);
        ESP_LOGI(currTAG , "ADC READ: %d\r\n", adc_data[0]);
    }
    return tension;
}