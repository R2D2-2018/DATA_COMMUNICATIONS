#include "access_buffers.hpp"
#include "i2c_esp_to_esp.hpp"

extern "C" {
void app_main();
}

void app_main() {
    ///< masterAndSlave demo code -- uncomment to activate
    AccessBuffers accessBuffers;

    // xTaskCreate(accessBuffers.printMasterSlaveBuffer, "masterAndSlave", 1024 * 2, (void *)1, 10, NULL);

    ///< master - slave demo code -- uncomment to activate
    /// xTaskCreate(master, "master", 1024 * 2, (void *)1, 10, NULL);
    xTaskCreate(accessBuffers.masterPrintBuffer, "master", 1024 * 2, (void *)1, 10, NULL);
}
