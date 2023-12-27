#ifndef DHT11_H
#define DHT11_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "rom/ets_sys.h"

#define MAX_TIMING 85

int read_dht(int pin, float* temperature, float* humidity);

#endif 