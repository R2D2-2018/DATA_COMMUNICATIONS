#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "LED.hpp"

extern "C" {
   void app_main();
}

void app_main() {
    auto led = LED();
    led.blinkInfinitly(1000);
}
