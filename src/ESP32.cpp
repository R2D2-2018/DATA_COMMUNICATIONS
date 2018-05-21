/**
 * @file
 * @brief     ESP32 class - containing (SPI) commands.
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#include "ESP32.hpp"

ESP32::ESP32(){
}

void ESP32::reset(){	
}

int ESP32::readRegister(int address){
	return address;
}

void ESP32::writeRegister(int address, std::array<uint8_t, 2> data) {
    auto comm = Command(1, address);
    comm.setData(data);
    comm.sendCommand();
}

void ESP32::setBit(){
}

void ESP32::eraseBit(){
}

int ESP32::readBuffer(){
	return 0;
}

void ESP32::writeBuffer(int data){
}
