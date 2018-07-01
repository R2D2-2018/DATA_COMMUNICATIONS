/**
 * @file
 * @brief     esp32 class - containing (SPI) commands.
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#include "esp32.hpp"

esp32::esp32() {
}

void esp32::reset() {
}

int esp32::readRegister(int address) {
    return address;
}

void esp32::writeRegister(int address, std::array<uint8_t, 2> data) {
}

void esp32::setBit() {
}

void esp32::eraseBit() {
}

int esp32::readBuffer() {
    return 0;
}

void esp32::writeBuffer(int data) {
}
