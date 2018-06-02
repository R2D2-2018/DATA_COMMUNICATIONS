/**
 * @file
 * @brief     I2C class for the ESP32
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#ifndef I2C_ESP_HPP
#define I2C_ESP_HPP

#include <memory>
#include "driver/i2c.h"

///< SLAVE ADDRESS AND RW BIT CONFIGURATION
static constexpr i2c_rw_t writeBit = i2c_rw_t::I2C_MASTER_WRITE;	///< Master WRITE bit
static constexpr i2c_rw_t readBit = i2c_rw_t::I2C_MASTER_READ;		///< Master READ bit

///< ACK CONFIGURATION
static constexpr i2c_ack_type_t masterAck = i2c_ack_type_t::I2C_MASTER_ACK;	///< Master ACK value
static constexpr i2c_ack_type_t masterNack = i2c_ack_type_t::I2C_MASTER_NACK;	///< Master NACK value (false)

class I2cEsp {
private:
	int dataBufferLength = 512; 				///< Data buffer length
	int txBufferLength = 2 * dataBufferLength;	///< Transmission buffer length
	int rxBufferLength = 2 * dataBufferLength;	///< Receiving buffer length
	
	uint8_t * dataBuffer;	///< Data buffer
	uint8_t * txBuffer;		///< Tranmission buffer
	uint8_t * rxBuffer;		///< Receive buffer
	
	bool isMaster;			///< Operating mode: true = master; false = slave
	bool checkAck;			///< Whether to check for ACKs
	
	static constexpr int masterClockFrequency = 100000;
	static constexpr uint8_t slaveAddress = 0x28;
	
	i2c_port_t portNum;		///< I2C port number: could be port 0 or port 1
	gpio_num_t scl;			///< Serial Clock pin
	gpio_num_t sda;			///< Data pin
	
public:
	/**
	* @brief Constructor of class
	*
	* Fills in the config for master if isMaster = true; slave if false, and
	* instantiates the buffers with their respective bufferLenghts.
	*
	* @param[in]     gpio_num_t sda   GPIO pin for data 
	* @param[in]     gpio_num_t scl   GPIO pin for Serial Clock
	* @param[in]     bool isMaster    Whether device is master; false by default
	*/
	I2cEsp(gpio_num_t sda, gpio_num_t slc, bool isMaster = false);
	/**
	* @brief Deconstructor of class
	*
	* Deletes buffers made in constructor to release resources
	*
	*/
	~I2cEsp();
	
	/**
	* @brief Read output from connected device
	*
	* Read output from the connected device and place it in
	* the rxBuffer (receive buffer) using the I2C protocol.
	*
	* @return 0 if everything went the way it should; -1 if not
	*/
	int read();
	/**
	* @brief Write input to connected device
	*
	* Write input from txBuffer (transmission buffer) to the
	* connected device using the I2C protocol.
	*
	* @return void
	*/
	void write();
	
	/**
	* @brief Print contents of buffer
	*
	* Print the contents of the transmission- or receive buffer.
	*
	* @return void
	*/
	void print();
	
};

#endif ///< I2C_ESP_HPP