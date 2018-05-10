/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <vector>

extern "C" {
   void app_main();
}

void app_main() {
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    int level = 0;

    uint32_t* GPIO_w1ts = (uint32_t*)0x3ff44008;
    uint32_t* GPIO_w1tc = (uint32_t*)0x3ff4400c;

    while (true) {
        printf("Hello, world.\n");
        if (level) {
            *GPIO_w1ts = 1 << 2;
        } else {
            *GPIO_w1tc = 1 << 2;
        }
        level = !level;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
