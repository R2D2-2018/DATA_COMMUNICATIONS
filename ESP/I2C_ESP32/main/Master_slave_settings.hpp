#ifndef MASTERSLAVESETTINGS_HPP
#define MASTERSLAVESETTINGS_HPP

//#include "MasterSlaveSettings.hpp"

class MasterSlaveSettings {
  private:
    static constexpr int delayTimeBetweenItemsMS = 1000; ///< Delay time between loop iterations
  public:
    MasterSlaveSettings();

    static void masterAndSlave(void *taskID);

    static void master(void *taskID);

    static void slave(void *taskID);
};

#endif