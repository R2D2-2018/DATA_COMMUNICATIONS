#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "command.hpp"
#include "LED.hpp"
#include "SPI.hpp"

#include <cstring>

#include <vector>

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

    std::vector<char> dest;

    for (int i = 0; i < 2; ++i) {
        bus.waitForTransaction();
        bus.printRecv(dest);
    }

    printf("Received data\n");
    printf("Size: %d\n", dest.size());

    auto comm = Command(dest);
    comm.process();

    for (auto item : dest) {
        printf("%d", item);
    }

    if (dest[0] == 0xA2 && dest[7] == 0x1C) {
        led.blinkInfinitly(500);
    }

    return;
}
