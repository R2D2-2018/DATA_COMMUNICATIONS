#ifndef ACCESS_BUFFERS_HPP
#define ACCESS_BUFFERS_HPP

#include "I2C_ESP_to_ESP.hpp"
#include "esp_log.h"
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

    /**
 * @brief returns the master RX buffer
 *
 * @description This function uses the I2C_ESP_to_ESP class to read the resieve buffer and then returns the buffer
 * in pointer form. If an error occors then then a default buffer will be returned.
 * 
 * @return 
 * buffer : uint8_t*
 */
    static uint8_t * masterRead(void *taskID);

        /**
 * @brief set the TX master buffer
 *
 * @description This function uses the I2C_ESP_to_ESP class to set the transmition master buffer with the parameter buffer.
 * If error from the esp-idf toolchain occor these erros will be printed.
 * 
 * @parm 
 * buffer : uint8_t *
 * bufferLength : int
 */
    static bool masterWrite(uint8_t *buffer, int bufferLength);

        /**
 * @brief reads and prints the master buffer
 *
 * @description This function uses the I2C_ESP_to_ESP class to read the RX master buffer and prints it. 
 * If error from the esp-idf toolchain occor these erros will be printed as well.
 * 
 */
    static void masterPrintBuffer(void *taskID);

        /**
 * @brief returns the slave RX buffer
 *
 * @description This function uses the I2C_ESP_to_ESP class to read the resieve slave buffer and then returns the buffer
 * in pointer form. If an error occors then then a default buffer will be returned.
 * 
 * @return 
 * buffer : uint8_t*
 */
    static uint8_t * slaveRead(void *taskID);

  /**
 * @brief set the TX slave buffer
 *
 * @description This function uses the I2C_ESP_to_ESP class to set the transmition slave buffer with the parameter buffer.
 * If error from the esp-idf toolchain occor these erros will be printed.
 * 
 * @parm 
 * buffer : uint8_t *
 * bufferLength : int
 */
    static bool slaveWrite(uint8_t *buffer, int bufferLength);

        /**
 * @brief reads and prints the RX slave buffer
 *
 * @description This function uses the I2C_ESP_to_ESP class to read the resieve slave buffer and prints it. 
 * If error from the esp-idf toolchain occor these erros will be printed as well.
 * 
 */
    static void slavePrintBuffer(void *taskID);

    /**
     * @brief fills a buffer with standard values
     *
     * @description This function takes a buffer and fills it with values 0 to bufferLength. The reason this
     * function is made is to make sure the buffer is cleared before it's filled again.
     *
     * @parm
     * buffer : uint8_t* //The buffer buffer
     * bufferLength : int
     */
    static void getDefaultArray(uint8_t *buffer, int bufferLength);
};

#endif // ACCESS_BUFFERS_HPP