#ifndef wifi_HPP
#define wifi_HPP

// #include "I2C_ESP.hpp"
#include <iostream>

/**
 * @file      wifi.hpp
 * @brief     This class can preform data communication through wifi.
 * @author    Kiet van Osnabrugge
 * @license   MIT
 */
class wifi {
  private:
  public:
    wifi();

    /**
     * @brief receives data via wifi
     *
     * @description
     *
     * @return
     * buffer : uint8_t *
     */
    uint8_t *readwifiBuffer(); // This function if currently empty

    /**
     * @brief sends data via wifi
     *
     * @description
     *
     * @parm
     * txBuffer : uint8_t*
     * size : size_t
     */
    void writewifiBuffer(uint8_t *txBuffer, size_t size); // This function is currently empty
};

#endif