#ifndef ACCESBUFFERS_HPP
#define ACCESBUFFERS_HPP

#include "I2C_ESP.hpp"
#include <iostream>

/**
 * @file      Acces_buffers.hpp
 * @brief     This class uses the I2cEsp class to acces the buffers of the master and the slave esp
 * @author    Kiet van Osnabrugge and Roxanne van der Pol
 * @license   MIT
 */
class AccesBuffers {
  private:
    static constexpr int delayTimeBetweenItemsMS = 1000; ///< Delay time between loop iterations

  public:
    AccesBuffers();

    /**
     * @brief returns the master and slave buffer
     *
     * @description
     *
     * @return
     * buffer : uin8_t *
     */
    static uint8_t *getMasterSlaveBuffer(void *taskID); // These function if currently empty
    /**
     * @brief prints the master and slave buffer with error messages
     *
     * @description This function prints the master and the slave buffer. During the process of filling the buffers and printing
     * them parameters of the esp are checked. And some parameters give information about faulty useage and will give an error
     * print. There is no clear explanation of the error yet.
     */
    static void printMasterSlaveBuffer(void *taskID);

    /**
     * @brief returns the slave buffer
     *
     * @description
     *
     * @return
     * buffer : uin8_t *
     */
    static uint8_t *getMasterSlaveBuffer(void *taskID); // These function if currently empty
    /**
     * @brief prints the slave buffer with error messages
     *
     * @description This function prints the slave buffer. During the process of filling the buffers and printing them parameters of
     * the esp are checked. And some parameters give information about faulty useage and will give an error print. There is no clear
     * explanation of the error yet.
     */
    static void printMasterBuffer(void *taskID);

    /**
     * @brief returns the master buffer
     *
     * @description
     *
     * @return
     * buffer : uin8_t *
     */
    static uint8_t *getSlaveBuffer(void *taskID); // These function if currently empty

    /**
     * @brief prints the master buffer with error messages
     *
     * @description This function prints the master buffer. During the process of filling the buffers and printing them parameters
     * of the esp are checked. And some parameters give information about faulty useage and will give an error print. There is no
     * clear explanation of the error yet.
     */
    static void printSlaveBuffer(void *taskID);

    static uint8_t *getDefaultArray(uint8_t *data, int dataLength); // These function if currently empty
};

#endif