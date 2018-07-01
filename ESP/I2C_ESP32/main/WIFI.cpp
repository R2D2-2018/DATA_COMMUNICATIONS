#include "WIFI.hpp"
#include <iostream>

wifi::wifi(){};

uint8_t * wifi::readWifiBuffer() {
    std::cout << "read via wifi\n";
    uint8_t buffer[1] = {0};
    return buffer;
};

void wifi::writeWifiBuffer(uint8_t *txBuffer, size_t size) {
    std::cout << "write via wifi\n";
};