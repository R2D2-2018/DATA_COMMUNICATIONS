#ifndef ACCESS_BUFFERS_HPP
#define ACCESS_BUFFERS_HPP

#include "I2C_ESP_to_ESP.hpp"
#include <iostream>

/**
 * @file      Acces_buffers.hpp
 * @brief     This class uses the I2cEsp class to acces the buffers of the master and the slave esp
 * @author    Kiet van Osnabrugge and Roxanne van der Pol
 * @license   MIT
 */
class AccessBuffers {
  private:
    static constexpr int delayTimeBetweenItemsMS = 1000; ///< Delay time between loop iterations

  public:
    AccessBuffers();

    static uint8_t * masterRead(void *taskID);
    static void masterWrite(uint8_t *data, int dataLength, void *taskID);
    static void masterPrintBuffer(void *taskID);

    static uint8_t * slaveRead(void *taskID);
    static void slaveWrite(uint8_t *data, int dataLength, void *taskID);
    static void slavePrintBuffer(void *taskID);

    /**
     * @brief returns the master and slave buffer
     *
     * @description
     *
     * @return
     * buffer : uin8_t *
     */
    //static uint8_t *getMasterSlaveBuffer(void *taskID); // This function is currently empty
    
    /**
     * @brief prints the master and slave buffer with error messages
     *
     * @description This function prints the master and the slave buffer. During the process of filling the buffers and printing
     * them parameters of the esp are checked. And some parameters give information about faulty useage and will give an error
     * print. There is no clear explanation of the error yet.
     */
    //static void printMasterSlaveBuffer(void *taskID);

    /**
     * @brief returns the slave buffer
     *
     * @description
     *
     * @return
     * buffer : uin8_t *
     */
    //static uint8_t *getMasterBuffer(void *taskID); // This function is currently empty
    /**
     * @brief prints the slave buffer with error messages
     *
     * @description This function prints the slave buffer. During the process of filling the buffers and printing them parameters of
     * the esp are checked. And some parameters give information about faulty useage and will give an error print. There is no clear
     * explanation of the error yet.
     */
    //static void printMasterBuffer(void *taskID);

    /**
     * @brief returns the master buffer
     *
     * @description
     *
     * @return
     * buffer : uin8_t *
     */
    //static uint8_t *getSlaveBuffer(void *taskID); // This function is currently empty

    /**
     * @brief prints the master buffer with error messages
     *
     * @description This function prints the master buffer. During the process of filling the buffers and printing them parameters
     * of the esp are checked. And some parameters give information about faulty useage and will give an error print. There is no
     * clear explanation of the error yet.
     */
    //static void printSlaveBuffer(void *taskID);

    /**
     * @brief fills a buffer with standard values
     *
     * @description This function takes a buffer and fills it with values 0 to dataLength. The reason this
     * function is made is to make sure the buffer is cleared before it's filled again.
     *
     * @parm
     * data : uint8_t* //The data buffer
     * dataLength : int
     *
     * @return
     * data : uint8_t*
     */
    static void getDefaultArray(uint8_t *data, int dataLength);
};

#endif // ACCESS_BUFFERS_HPP