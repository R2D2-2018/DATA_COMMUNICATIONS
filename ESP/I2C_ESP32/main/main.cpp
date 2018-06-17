#include "AccesBuffers.hpp"
#include "I2C_ESP.hpp"

extern "C" {
void app_main();
}

void app_main() {
    ///< masterAndSlave demo code -- uncomment to activate
    MasterSlaveSettings MSS;
    xTaskCreate(MSS.printMasterSlaveBuffer, "masterAndSlave", 1024 * 2, (void *)1, 10, NULL);

    ///< master - slave demo code -- uncomment to activate
    /// xTaskCreate(master, "master", 1024 * 2, (void *)1, 10, NULL);
    ///< xTaskCreate(slave, "slave", 1024 * 2, (void* ) 1, 10, NULL);
}
