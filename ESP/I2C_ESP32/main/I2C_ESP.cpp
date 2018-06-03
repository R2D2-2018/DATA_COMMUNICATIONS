#include "I2C_ESP.hpp"

/*
I2cEsp::I2cEsp(gpio_num_t & sda, gpio_num_t & scl, bool isMaster):
	isMaster(isMaster)
{
	if(isMaster) {
		i2c_port_t i2c_master_port = i2c_port_t::I2C_NUM_1;
		i2c_config_t conf;
		conf.mode = I2C_MODE_MASTER;
		conf.sda_io_num = sda;
		conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
		conf.scl_io_num = scl;
		conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
		conf.master.clk_speed = masterClockFrequency;
		i2c_param_config(i2c_master_port, &conf);
		i2c_driver_install(i2c_master_port, conf.mode,
						   rxBufferLength,
						   txBufferLength, 0);
	} else {
		i2c_port_t i2c_slave_port = i2c_port_t::I2C_NUM_0;
		i2c_config_t conf_slave;
		conf_slave.sda_io_num = sda;
		conf_slave.sda_pullup_en = GPIO_PULLUP_ENABLE;
		conf_slave.scl_io_num = scl;
		conf_slave.scl_pullup_en = GPIO_PULLUP_ENABLE;
		conf_slave.mode = I2C_MODE_SLAVE;
		conf_slave.slave.addr_10bit_en = 0;
		conf_slave.slave.slave_addr = slaveAddress;
		i2c_param_config(i2c_slave_port, &conf_slave);
		i2c_driver_install(i2c_slave_port, conf_slave.mode,
						   rxBufferLength,
						   txBufferLength, 0);	
	}
	
	dataBuffer = new uint8_t[dataBufferLength];
	txBuffer = new uint8_t[dataBufferLength];
	rxBuffer = new uint8_t[dataBufferLength];
	
}

I2cEsp::~I2cEsp(){
	delete dataBuffer;
	delete txBuffer;
	delete rxBuffer;
}

int I2cEsp::read(){
	size_t size = 64;
	
	if(isMaster) {
		if(size == 0) {
			return ESP_OK;
		}
		i2c_cmd_handle_t cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, ( slaveAddress << 1 ) | readBit, checkAck);
		if(size > 1) {
			//i2c_master_read(cmd, rxBuffer, size - 1, masterAck);
			i2c_master_read(cmd, rxBuffer, size, masterAck);
		}
		//i2c_master_read_byte(cmd, rxBuffer + size - 1, masterNack);
		i2c_master_read_byte(cmd, rxBuffer + size, masterNack);
		i2c_master_stop(cmd);
		esp_err_t ret = i2c_master_cmd_begin(portNum, cmd, 1000 / portTICK_RATE_MS);
		i2c_cmd_link_delete(cmd);
		return ret;
		
	} else {
		int ret = i2c_slave_read_buffer( portNum, rxBuffer, size, 1000 / portTICK_RATE_MS);
		return ret;
	}
}

int I2cEsp::write(uint8_t * data, size_t size){

	if(isMaster) {
		i2c_cmd_handle_t cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, ( slaveAddress << 1 ) | writeBit, checkAck);
		i2c_master_write(cmd, data, size, checkAck);
		i2c_master_stop(cmd);
		esp_err_t ret = i2c_master_cmd_begin(portNum, cmd, 1000 / portTICK_RATE_MS);
		i2c_cmd_link_delete(cmd);
		return ret;
	} else {
		size_t ret = i2c_slave_write_buffer(portNum, data, size, 1000 / portTICK_RATE_MS);
		return ret;
	}

}

void I2cEsp::print(uint8_t * buffer, int bufferLength){
	std::cout << std::hex;
	for(int i = 0; i < bufferLength; ++i) {
		std::cout << int(buffer[i]) << ' ';
		if((i + 1) % 16 == 0) {
			std::cout << '\n';
		}
	}
	std::cout << '\n';
	std::cout << std::dec;
}

void I2cEsp::modifyBufferData(int mode) {
	switch(mode) {
		case 1: {
			for(int i = 0; i < dataBufferLength; ++i) {
				dataBuffer[i] = dataBuffer[i] - 1;
			}
		} case 2: {
			for(int i = 0; i < dataBufferLength; ++i) {
				dataBuffer[i] = dataBuffer[i] * 2;
			}
		} case 3: {
			for(int i = 0; i < dataBufferLength; ++i) {
				dataBuffer[i] = 0xA;
			}
		} default: {
			for(int i = 0; i < dataBufferLength; ++i) {
				dataBuffer[i] = dataBuffer[i] + 1;
			}
		}
	};
}

///< GETTER FUNCTIONS
uint8_t * I2cEsp::getDataBuffer() {
	return dataBuffer;
}
uint8_t * I2cEsp::getTxBuffer() {
	return txBuffer;
}
uint8_t * I2cEsp::getRxBuffer() {
	return rxBuffer;
}
///<
int I2cEsp::getDataBufferLength() {
	return dataBufferLength;
}
int I2cEsp::getTxBufferLength() {
	return txBufferLength;
}
int I2cEsp::getRxBufferLength() {
	return rxBufferLength;
}

*/