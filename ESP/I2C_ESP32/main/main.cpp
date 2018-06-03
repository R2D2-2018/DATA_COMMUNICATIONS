#include "LED.hpp"
#include "I2C_ESP.hpp"

constexpr int delayTimeBetweenItemsMS = 1234;	///< Delay time till next loop iteration

extern "C" {
   void app_main();
}

static void master(void * ID) {
    uint32_t taskID = (uint32_t) ID;
	
	gpio_num_t masterSDA = gpio_num_t::GPIO_NUM_18;
	gpio_num_t masterSLC = gpio_num_t::GPIO_NUM_19;
	
	I2cEsp master(masterSDA, masterSLC, true);
	
	int bufferLen = 32;
	uint8_t buffer[bufferLen];
	
	for(int i = 0; i < bufferLen; ++i) {
		buffer[i] = i;
	}
	
	std::cout << "=========================\n";
	
	std::cout << "Master.write()\n";
	master.write(buffer, bufferLen);
	master.print(master.getTxBuffer(), master.getTxBufferLength());
	
	while(1) {
	
	std::cout << "Master.read()\n";
	master.read();
	master.print(master.getRxBuffer(), master.getRxBufferLength());

	std::cout << "Master.write()\n";
	master.write(master.getDataBuffer(), master.getDataBufferLength());
	master.print(master.getTxBuffer(), master.getTxBufferLength());
		
	std::cout << "=========================\n";

	vTaskDelay(( delayTimeBetweenItemsMS * ( taskID + 1 ) ) / portTICK_RATE_MS);	
	}
}

static void slave(void * ID) {
	uint32_t taskID = (uint32_t) ID;

	gpio_num_t slaveSDA = gpio_num_t::GPIO_NUM_25;
	gpio_num_t slaveSLC = gpio_num_t::GPIO_NUM_26;
	
	I2cEsp slave(slaveSDA, slaveSLC, false);
	
	//std::cout << "=========================\n";
	
	while(1) {
	
	//std::cout << "Slave.read()\n";
	slave.read();
	//slave.print(slave.getRxBuffer(), 64);	
	
	//std::cout << "Modifying buffer data...\n\n";
	slave.modifyBufferData();
	
	//std::cout << "Slave.write()\n";
	slave.write(slave.getDataBuffer(), slave.getDataBufferLength());
	//slave.print(slave.getTxBuffer(), 64);
		
	//std::cout << "=========================\n";

	vTaskDelay(( delayTimeBetweenItemsMS * ( taskID + 1 ) ) / portTICK_RATE_MS);	
	}
}

static void masterAndSlave(void * ID) {
    uint32_t taskID = (uint32_t) ID;
	
	
	gpio_num_t masterSDA = gpio_num_t::GPIO_NUM_18;
	gpio_num_t masterSLC = gpio_num_t::GPIO_NUM_19;
	
	gpio_num_t slaveSDA = gpio_num_t::GPIO_NUM_25;
	gpio_num_t slaveSLC = gpio_num_t::GPIO_NUM_26;
	
	I2cEsp master(masterSDA, masterSLC, true);
	I2cEsp slave(slaveSDA, slaveSLC, false);

	int bufferLen = 64;
	uint8_t buffer[bufferLen];
	
	for(int i = 0; i < bufferLen; ++i) {
		buffer[i] = i;
	}
	
	while(1) {
	
		std::cout << "=========================\n";

		master.write(buffer, bufferLen);

		slave.read();
		std::cout << "SLAVE READ\n";
		slave.print(slave.getRxBuffer(), bufferLen);
		
		slave.modifyBufferData();
		
		slave.write(slave.getRxBuffer(), slave.getRxBufferLength());
		std::cout << "SLAVE WRITE\n";
		slave.print(slave.getRxBuffer(), bufferLen);
		
		master.read();
		std::cout << "MASTeR READ\n";
		master.print(master.getRxBuffer(), bufferLen);
		master.print(master.getTxBuffer(), bufferLen);
		master.print(master.getDataBuffer(), bufferLen);

		std::cout << "=========================\n";

		vTaskDelay(( delayTimeBetweenItemsMS * ( taskID + 1 ) ) / portTICK_RATE_MS);	
	}
}

void app_main() {
	xTaskCreate(masterAndSlave, "masterAndSlave", 1024 * 2, (void* ) 1, 10, NULL);
	//xTaskCreate(master, "master", 1024 * 2, (void* ) 1, 10, NULL);
	//xTaskCreate(slave, "slave", 1024 * 2, (void* ) 1, 10, NULL);
}
