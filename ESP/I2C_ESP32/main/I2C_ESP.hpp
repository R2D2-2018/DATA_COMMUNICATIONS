/**
 * @file
 * @brief     INSERT A DESCRIPTION HERE
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#ifndef I2C_ESP_HPP
#define I2C_ESP_HPP

#include <iostream>
#include "driver/i2c.h"

class I2cEsp {
private:
	///< ACK CONFIGURATION
	static constexpr bool checkAck = true;											///< Whether master will check from ACKs from slave
	static constexpr i2c_ack_type_t masterAck = i2c_ack_type_t::I2C_MASTER_ACK;		///< Master ACK value
	static constexpr i2c_ack_type_t masterNack = i2c_ack_type_t::I2C_MASTER_NACK;	///< Master NACK value (false)
	
	///< SLAVE ADDRESS AND RW BIT CONFIGURATION
	static constexpr uint8_t slaveAddress = 0x28;						///< ESP32 slave address
	static constexpr i2c_rw_t writeBit = i2c_rw_t::I2C_MASTER_WRITE;	///< Master WRITE bit
	static constexpr i2c_rw_t readBit = i2c_rw_t::I2C_MASTER_READ;		///< Master READ bit
	
	static constexpr int masterClockFrequency = 100000;					///< Master clock frequency

	static constexpr int dataLength = 512; 		///< Length of buffers
	static constexpr int rwBufferLength = 64; 	///< any value from 0 - dataLength
	
	int txBufferLength; ///< Transmission buffer size
	int rxBufferLength;	///< Receiving buffer size
	
	gpio_num_t sda;
	gpio_num_t scl;
	i2c_port_t portNum;
	
	uint8_t * dataBuffer = new uint8_t[dataLength];
	uint8_t * txBuffer = new uint8_t[dataLength];
	uint8_t * rxBuffer = new uint8_t[dataLength];
	
	bool isMaster = false;
	
public:	
	I2cEsp( const gpio_num_t & sda, const gpio_num_t & scl, const i2c_port_t & portNum = i2c_port_t::I2C_NUM_0, bool isMaster = false );
	~I2cEsp();

	esp_err_t read();
	esp_err_t write(uint8_t * txBuffer, size_t size = rwBufferLength);

	void printBuffer(uint8_t* buffer, int len);

	void modifyData();
	void modifyRx();
	void modifyTx();

	uint8_t * getDataBuffer();
	uint8_t * getRxBuffer();
	uint8_t * getTxBuffer();

	int getRwBufferLength();

};

#endif ///< I2C_ESP_HPP