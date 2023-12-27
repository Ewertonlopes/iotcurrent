#include "dht11.h"

int read_dht(int pin, float* temperature, float* humidity)
{
    int dht11_transfer[5]           = {0,0,0,0,0};
    int laststate                   = 1;
    int counter                     = 0;
    int j                           = 0;
    float temp                      = 0.0f;

    gpio_set_direction(pin, GPIO_MODE_DEF_OUTPUT);
    gpio_set_level(pin, 0);
    vTaskDelay(pdMS_TO_TICKS(18));
    
    gpio_set_level(pin, 1);
    ets_delay_us(40);

    gpio_set_direction(pin, GPIO_MODE_DEF_INPUT);

    for(int i = 0;i<MAX_TIMING;i++)
    {
        counter = 0;
        while(gpio_get_level(pin) == laststate)
        {
            counter++;
            ets_delay_us(1);
            if(counter == 255)
            {
                break;
            }
        }
        laststate = gpio_get_level(pin);

        if (counter == 255)
        {
            break;
        }
        
        if((i >=4 ) && (i%2 == 0))
        {
            dht11_transfer[j/8] <<= 1;
            if(counter > 16) dht11_transfer[j/8] |= 1;
            j++;
        }
    }

    if((j>=40) && dht11_transfer[4] ==
                            ((dht11_transfer[3] + dht11_transfer[2] + 
                            dht11_transfer[1] + dht11_transfer[0]) && 0xFF))
    {
        printf("Humidity = %d.%d %% Temperature = %d.%d *C\n",dht11_transfer[0],dht11_transfer[1],dht11_transfer[2],dht11_transfer[3]);
    }
    else
    {
        printf("Humidity = %d.%d %% Temperature = %d.%d *C\n",dht11_transfer[0],dht11_transfer[1],dht11_transfer[2],dht11_transfer[3]);
        return 1;
    }
    return 0;
}