#include "WIFI.hpp"
#include <iostream>

WIFI::WIFI(){};

uint8_t * WIFI::readWifiBuffer() {
    std::cout << "read via wifi\n";
    uint8_t buffer[1] = {0};
    return buffer;
};

void WIFI::writeWifiBuffer(uint8_t *txBuffer, size_t size) {
    std::cout << "write via wifi\n";
};