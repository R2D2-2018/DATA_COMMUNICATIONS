#include "wifi.hpp"
#include <iostream>

Wifi::wifi(){};

uint8_t *Wifi::readwifiBuffer() {
    std::cout << "read via wifi\n";
    uint8_t buffer[1] = {0};
    return buffer;
};

void Wifi::writewifiBuffer(uint8_t *txBuffer, size_t size) {
    std::cout << "write via wifi\n";
};