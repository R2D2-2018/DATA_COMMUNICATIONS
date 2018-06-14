#ifndef MASTERSLAVESETTINGS_HPP
#define MASTERSLAVESETTINGS_HPP

#include "I2C_ESP.hpp"
#include <iostream>

class MasterSlaveSettings {
  private:
    static constexpr int delayTimeBetweenItemsMS = 1000; ///< Delay time between loop iterations

  public:
    MasterSlaveSettings();

    static void masterAndSlave(void *taskID);

    static void getDefaultArray(uint8_t data[], int dataLength);

    static void master(void *taskID);

    static void slave(void *taskID);
};

#endif