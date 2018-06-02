#ifndef I2C_ESP_HPP
#define I2C_ESP_HPP

#include "driver/i2c.h"

///< SLAVE ADDRESS AND RW BIT CONFIGURATION
constexpr i2c_rw_t writeBit = i2c_rw_t::I2C_MASTER_WRITE;	///< Master WRITE bit
constexpr i2c_rw_t readBit = i2c_rw_t::I2C_MASTER_READ;		///< Master READ bit

///< ACK CONFIGURATION
constexpr i2c_ack_type_t masterAck = i2c_ack_type_t::I2C_MASTER_ACK;	///< Master ACK value
constexpr i2c_ack_type_t masterNack = i2c_ack_type_t::I2C_MASTER_NACK;	///< Master NACK value (false)

class I2cEsp {
private:
	int dataBufferLength = 512; 				///< Data buffer length
	int txBufferLength = 2 * dataBufferLength;	///< Transmission buffer length
	int rxBufferLength = 2 * dataBufferLength;	///< Receiving buffer length
	
	uint8_t * dataBuffer;
	uint8_t * txBuffer;
	uint8_t * rxBuffer;
	
	bool isMaster;
	bool checkAck;
	
	int masterClockFrequency = 100000;
	uint8_t slaveAddress = 0x28;
	
	i2c_port_t portNum;
	gpio_num_t scl;
	gpio_num_t sda;
	
public:
	I2cEsp(gpio_num_t sda, gpio_num_t slc, bool isMaster = false);
	~I2cEsp();
	
	int read();
	void write();
	
	void print();
	
};

#endif ///< I2C_ESP_HPP