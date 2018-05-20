#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "LED.hpp"
#include "SPI.hpp"

extern "C" {
   void app_main();
}

void app_main() {
    auto led = LED();
    [[maybe_unused]] auto bus = SPI();

    //auto retValue = bus.SPIInit();
    /*
    if(!retValue) {
        printf("Slave init failed");
        led.blinkInfinitly(1000);
    }
    */


    while (true) {
        bus.waitForTransaction();
        bus.printRecv();
    }

    printf("Received data");
    //led.blinkInfinitly(1000);
}
