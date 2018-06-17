#ifndef ACCESBUFFERS_HPP
#define ACCESBUFFERS_HPP

#include "I2C_ESP.hpp"
#include <iostream>

class AccesBuffers {
  private:
    static constexpr int delayTimeBetweenItemsMS = 1000; ///< Delay time between loop iterations

  public:
    AccesBuffers();

    static void getMasterSlaveBuffer(void *taskID);
    static void printMasterSlaveBuffer(void *taskID);

    static void getMasterSlaveBuffer(void *taskID);
    static void printMasterBuffer(void *taskID);

    static void getSlaveBuffer(void *taskID);
    static void printSlaveBuffer(void *taskID);

    static void getDefaultArray(uint8_t *data, int dataLength);
};

#endif