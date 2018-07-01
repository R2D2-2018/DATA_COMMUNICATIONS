/**
 * @file
 * @brief     I2C class for the ESP32
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#ifndef I2C_ESP_TO_ESP_HPP
#define I2C_ESP_TO_ESP_HPP

#include "driver/i2c.h"
#include <iostream>

class i2cEsp {
  private:
    ///ACK CONFIGURATION
    static constexpr bool checkAck             = true;                           ///< Whether master will check from ACKs from slave
    static constexpr i2c_ack_type_t masterAck  = i2c_ack_type_t::I2C_MASTER_ACK; ///< Master ACK value
    static constexpr i2c_ack_type_t masterNack = i2c_ack_type_t::I2C_MASTER_NACK; ///< Master NACK value (false)

    ///SLAVE ADDRESS AND RW BIT CONFIGURATION
    static constexpr uint8_t slaveAddress = 0x28;                       ///< ESP32 slave address
    static constexpr i2c_rw_t writeBit    = i2c_rw_t::I2C_MASTER_WRITE; ///< Master WRITE bit
    static constexpr i2c_rw_t readBit     = i2c_rw_t::I2C_MASTER_READ;  ///< Master READ bit

    static constexpr int masterClockFrequency = 100000; ///< Master clock frequency

    static constexpr int dataLength     = 512; ///< Length of buffers
    static constexpr int rwBufferLength = 64;  ///< any value from 0 - dataLength

    int txBufferLength; ///< Transmission buffer size
    int rxBufferLength; ///< Receiving buffer size

    gpio_num_t sda;
    gpio_num_t scl;
    i2c_port_t portNum;

    uint8_t *dataBuffer = new uint8_t[dataLength];
    uint8_t *txBuffer   = new uint8_t[dataLength];
    uint8_t *rxBuffer   = new uint8_t[dataLength];

    bool isMaster = false;

  public:
    /**
     * @brief Constructor of class
     *
     * Fills in the config for master if isMaster = true; slave if false, and
     * instantiates the buffers with their respective bufferLenghts.
     *
     * @param[in]     gpio_num_t &sda   GPIO pin for data
     * @param[in]     gpio_num_t &scl   GPIO pin for Serial Clock
     * @param[in]     i2c_port_t	&portNum   I2C port number; i2c_port_t::I2C_NUM_0 by default
     * @param[in]     bool isMaster    Whether device is master; false by default
     */
    i2cEsp(const gpio_num_t &sda, const gpio_num_t &scl, const i2c_port_t &portNum = i2c_port_t::I2C_NUM_0, bool isMaster = false);
    ~i2cEsp();

    /**
     * @brief Read output from connected device
     *
     * Read output from the connected device and place it in
     * the rxBuffer (receive buffer) in case of isMaster = true,
     * in dataBuffer in case of isMaster = false.
     *
     * @return	esp_err_t	state code; ESP_OK if everything went fine
     */
    esp_err_t read();
    /**
     * @brief Write input to connected device
     *
     * Write input from txBuffer (transmission buffer) in case of isMaster = true,
     * dataBuffer in case of isMaster = false;
     *
     * @param[in]     uint8_t	*txBuffer	Data to be transferred
     * @param[in]     size_t		size		size of txBuffer; rwBufferLength by default
     *
     * @return	esp_err_t	state code; ESP_OK if everything went fine
     */
    esp_err_t write(uint8_t *txBuffer, size_t size = rwBufferLength);

    /**
     * @brief Print contents of buffer
     *
     * Print the contents of the input buffer
     *
     * @param[in]     uint8_t	*buffer	Buffer to be printed
     * @param[in]     int		len		size of buffer
     *
     * @return void
     */
    void printBuffer(uint8_t *buffer, int len);

    /**
     * @brief Modify contents of dataBuffer
     *
     * Perform += 1 on all dataBuffer items
     *
     * @return void
     */
    void modifyData();
    /**
     * @brief Modify contents of receive buffer
     *
     * Perform += 1 on all rxBuffer items
     *
     * @return void
     */
    void modifyRx();
    /**
     * @brief Modify contents of transmission buffer
     *
     * Perform += 1 on all txBuffer items
     *
     * @return void
     */
    void modifyTx();

    /**
     * @brief Getter for dataBuffer
     *
     * Returns uint8_t pointer to dataBuffer.
     *
     * @return	uint8_t *	dataBuffer
     */
    uint8_t *getDataBuffer();
    /**
     * @brief Getter for receive buffer
     *
     * Returns uint8_t pointer to rxBuffer.
     *
     * @return	uint8_t *	rxBuffer
     */
    uint8_t *getRxBuffer();
    /**
     * @brief Getter for transmission buffer
     *
     * Returns uint8_t pointer to txBuffer.
     *
     * @return	uint8_t *	txBuffer
     */
    uint8_t *getTxBuffer();

    /**
     * @brief Getter for rxBufferLength
     *
     * Returns the length of tx and rx buffers
     *
     * @return	int		rxBufferLength
     */
    int getRwBufferLength();
};

#endif ///< I2C_ESP_TO_ESP_HPP
