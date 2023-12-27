#ifndef UV_H
#define UV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/adc.h"
#include "esp_log.h"

static const char *uvTAG = "UV Sensor";

extern uint16_t uv_index_output;

void uv_task();
void uv_init();
uint16_t uv_read();

#endif 