#ifndef CURR_H
#define CURR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/adc.h"
#include "esp_log.h"

static const char *currTAG = "Current Sensor";

extern double curr_index_output;

void curr_task();
void curr_init();
double curr_read();

#endif 