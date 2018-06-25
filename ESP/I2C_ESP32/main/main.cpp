#include "access_buffers.hpp"
#include "i2c_esp_to_esp.hpp"

extern "C" {
void app_main();
}

void app_main() {
    AccessBuffers accessBuffers;
    xTaskCreate(accessBuffers.masterPrintBuffer, "master", 1024 * 2, (void *)1, 10, NULL);
}
