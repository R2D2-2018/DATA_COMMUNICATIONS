#include <iostream>
#include "driver/i2c.h"

///< DATA_LEN & DELAY_TIME CONFIGURATION
constexpr int dataLength = 512; 							///< Data buffer length for test_buffer
constexpr int rwTestLength = 64; 							///< Data length for r/w test, any value from 0 - dataLength
constexpr int delayTimeBetweenItemsMS = 1234;				///< Delay time between different test items

///< SLAVE_CONFIGURATION
constexpr gpio_num_t slaveSCL = gpio_num_t::GPIO_NUM_26;	///< GPIO number for slave CLK
constexpr gpio_num_t slaveSDA = gpio_num_t::GPIO_NUM_25;	///< GPIO number for slave DATA
constexpr i2c_port_t slavePortNum = i2c_port_t::I2C_NUM_0;	///< Slave port number
constexpr int slaveTransmissionBufferLen = 2*dataLength;	///< Slave transmission buffer size
constexpr int slaveReceivingBufferLen = 2*dataLength;		///< Slave receiving buffer size

//< MASTER CONFIGURATION
constexpr gpio_num_t masterSCL = gpio_num_t::GPIO_NUM_19;	///< GPIO number for master CLK
constexpr gpio_num_t masterSDA = gpio_num_t::GPIO_NUM_18;	///< GPIO number for master DATA
constexpr i2c_port_t masterPortNum = i2c_port_t::I2C_NUM_1;	///< Master port number
constexpr int masterTransmissionBufferLen = 0;				///< Master transmission buffer size
constexpr int masterReceivingBufferLen = 0;					///< Master receiving buffer size
constexpr int masterClockFrequency = 100000;				///< Master clock frequency

///< SLAVE ADDRESS AND RW BIT CONFIGURATION
constexpr uint8_t slaveAddress = 0x28;						///< ESP32 slave address
constexpr i2c_rw_t writeBit = i2c_rw_t::I2C_MASTER_WRITE;	///< Master WRITE bit
constexpr i2c_rw_t readBit = i2c_rw_t::I2C_MASTER_READ;		///< Master READ bit

///< ACK CONFIGURATION
constexpr bool checkAck = true;											///< Whether master will check from ACKs from slave
constexpr i2c_ack_type_t masterAck = i2c_ack_type_t::I2C_MASTER_ACK;	///< Master ACK value
constexpr i2c_ack_type_t masterNack = i2c_ack_type_t::I2C_MASTER_NACK;	///< Master NACK value (false)

SemaphoreHandle_t print_mux = NULL;

///< slave initialization
static void slaveInit() {
	i2c_port_t i2c_slave_port = slavePortNum;
	i2c_config_t conf_slave;
	conf_slave.sda_io_num = slaveSDA;
	conf_slave.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf_slave.scl_io_num = slaveSCL;
	conf_slave.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf_slave.mode = I2C_MODE_SLAVE;
	conf_slave.slave.addr_10bit_en = 0;
	conf_slave.slave.slave_addr = slaveAddress;
	i2c_param_config(i2c_slave_port, &conf_slave);
	i2c_driver_install(i2c_slave_port, conf_slave.mode,
					   slaveReceivingBufferLen,
					   slaveTransmissionBufferLen, 0);
}

///< Slave reads buffer contents and returns int buffer size
static int slaveReadBuffer(uint8_t * data) {
	int size = i2c_slave_read_buffer( slavePortNum, data, rwTestLength, 1000 / portTICK_RATE_MS);
	return size;
}

///< Slave writes to data buffer and returns size_t buffer size
static size_t slaveWriteBuffer(uint8_t * data) {
	size_t size = i2c_slave_write_buffer(slavePortNum, data, rwTestLength, 1000 / portTICK_RATE_MS);
	return size;
}

///< Print buffer contents
static void printBuffer(uint8_t* buf, int len) {
	std::cout << std::hex;
	int i;
	for(i = 0; i < len; i++) {
		std::cout << int(buf[i]) << ' ';
		if(( i + 1 ) % 16 == 0) {
			std::cout << '\n';
		}
	}
	std::cout << '\n';
	std::cout << std::dec;
}

static void slave(void * taskID) {
	int i = 0;
	uint32_t task_idx = (uint32_t) taskID;
	
	uint8_t * data = new uint8_t[dataLength];
	uint8_t * data_rd = new uint8_t[dataLength];
	uint8_t * data_wr = new uint8_t[dataLength];
	
	int count = 0;
	while(1) {
		std::cout << "==================\n";
		std::cout << "test count: " << count << "\n";
		std::cout << "==================\n";
		///< ------------------------------------------
		
		int size;
		
		///< Slave reads data from master
		size = slaveReadBuffer(data_rd);
		
		if(size) {
			std::cout << "Task[" << task_idx << "] slave read: [" << size << "] bytes:\n";
			printBuffer(data_rd, size);
			for (i = 0; i < dataLength; i++) {
				data_wr[i] = data_rd[i] + count;
			}
			count += 1;
		} else {
			std::cout << "Slave could not read data...\n";	
		}
		
		///< ------------------------------------------
			
		size_t d_size = slaveWriteBuffer(data_wr);
		
		if(d_size == 0) {
			std::cout << "slave transmission buffer is FULL!\n";
			std::cout << "Going back to start of allocated space...\n";
			data_wr = data_wr-dataLength;
		} else if(size){
			std::cout << "Task[" << task_idx << "] slave write: [" << size << "] bytes:\n";
			printBuffer(data_wr, d_size);
		} else {
			std::cout << "Slave could not write data...\n";
		}	
		vTaskDelay(( delayTimeBetweenItemsMS * ( task_idx + 1 ) ) / portTICK_RATE_MS);
	}
	delete data;
	delete data_wr;
	delete data_rd;
}

extern "C" void app_main() {
	
	slaveInit();
	xTaskCreate(slave, "slave", 1024 * 2, (void* ) 1, 10, NULL);
	
}


