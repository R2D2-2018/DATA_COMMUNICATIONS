/**
 * @file
 * @brief     esp32
 * class - containing (SPI) commands.
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#include "esp32.hpp"

Esp32::Esp32() {
}

void Esp32::reset() {
}

int Esp32::readRegister(int address) {
    return address;
}

void Esp32::writeRegister(int address, std::array<uint8_t, 2> data) {
}

void Esp32::setBit() {
}

void Esp32::eraseBit() {
}

int Esp32::readBuffer() {
    return 0;
}

void Esp32::writeBuffer(int data) {
}
