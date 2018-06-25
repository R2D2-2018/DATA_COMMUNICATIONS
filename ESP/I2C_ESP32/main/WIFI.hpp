#ifndef WIFI_HPP
#define WIFI_HPP

// #include "I2C_ESP.hpp"
#include <iostream>

/**
 * @file      WIFI.hpp
 * @brief     This class can preform data communication through wifi.
 * @author    Kiet van Osnabrugge
 * @license   MIT
 */
class WIFI {
  private:
  public:
    WIFI();

    /**
     * @brief resieves data via wifi
     *
     * @description
     *
     * @return
     * buffer : uint8_t *
     */
    uint8_t * readWifiBuffer(); // This function if currently empty

    /**
     * @brief sends data via wifi
     *
     * @description
     *
     * @parm
     * txBuffer : uint8_t*
     * size : size_t
     */
    void writeWifiBuffer(uint8_t *txBuffer, size_t size); // This function is currently empty
};

#endif