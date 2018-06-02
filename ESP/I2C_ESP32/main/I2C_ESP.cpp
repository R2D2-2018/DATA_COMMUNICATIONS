#include "I2C_ESP.hpp"

I2cEsp::I2cEsp(gpio_num_t sda, gpio_num_t slc, bool isMaster){
	
	i2c_config_t config;
	
	config.scl_io_num = scl;
	config.scl_pullup_en = GPIO_PULLUP_ENABLE;
	config.sda_io_num = sda;
	config.sda_pullup_en = GPIO_PULLUP_ENABLE;
	
	if(isMaster){
		config.mode = I2C_MODE_MASTER;
		config.master.clk_speed = masterClockFrequency;
	} else {
		config.mode = I2C_MODE_SLAVE;
		config.slave.addr_10bit_en = 0;
		config.slave.slave_addr = slaveAddress;
	}
	
	i2c_param_config(portNum, &config);
	i2c_driver_install(portNum, config.mode, rxBufferLength, txBufferLength, 0);
	
	dataBuffer = new uint8_t[dataBufferLength];
	txBuffer = new uint8_t[txBufferLength];
	rxBuffer = new uint8_t[rxBufferLength];
	
}

I2cEsp::~I2cEsp(){
	delete dataBuffer;
	delete txBuffer;
	delete rxBuffer;
}

int I2cEsp::read(){
	esp_err_t status;
	
	if(isMaster) {
		i2c_cmd_handle_t link = i2c_cmd_link_create();
		i2c_master_start(link);
		i2c_master_write_byte(link, ( slaveAddress << 1 ) | readBit, checkAck);
		
		if(rxBufferLength > 1) {
			i2c_master_read(link, rxBuffer, rxBufferLength - 1, masterAck);
		}
		i2c_master_read_byte(link, rxBuffer + rxBufferLength - 1, masterNack);
		i2c_master_stop(link);
		
		status = i2c_master_cmd_begin( portNum, link, 1000 / portTICK_RATE_MS);
		i2c_cmd_link_delete(link);
	
	} else {
		status = i2c_slave_read_buffer( portNum, rxBuffer, rxBufferLength, 1000 / portTICK_RATE_MS);
	}

	if(status != ESP_OK){
		return -1;
	}
	
	return 0;
}

void I2cEsp::write(){
	
}

void I2cEsp::print(){
		
}
