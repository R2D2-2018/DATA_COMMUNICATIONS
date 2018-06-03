#include "LED.hpp"
#include "I2C_ESP.hpp"

constexpr int delayTimeBetweenItemsMS = 500;				///< Delay time between different test items

extern "C" {
   void app_main();
}

///< Tasks which performs tests					Example:
///< 1. Slave buffer is filled with data	--> [1,2,3]
///< 2. Master reads data from slave		--> [1,2,3]
///< 2. Master writes data to slave			--> [7,7,7]
///< 3. Master reads data from slave		--> [7,7,7]
static void twoModesOneESP(void * taskID) {
	I2cEsp master(true);
	I2cEsp slave(false);
	
	int i = 0;
    int ret;
    uint32_t task_idx = (uint32_t) taskID;
	
	//uint8_t * data = new uint8_t[dataLength];
	uint8_t data[dataLength];
	
    int count = 0;
	
	for(i = 0; i < dataLength; i++) {
		data[i] = i;
	}
	size_t d_size = slave.write(data);
	if(d_size == 0) {
		std::cout << "slave transmission buffer is FULL!\n";
		ret = master.read(data, dataLength);
	} else {
		ret = master.read(data, rwTestLength);
	}
	
	std::cout << "TASK[" << task_idx << "] Slave buffer data:\n";
	slave.printBuffer(slave.getDataBuffer(), d_size);
	
    while(1) {
		std::cout << "==================\n";
		std::cout << "test count: " << count++ << "\n";
		std::cout << "==================\n";
		
		//std::cout << "MODIFY_DATA +1\n";
		//slave.modifyData();
		
        d_size = slave.write(slave.getDataBuffer());

        if(d_size == 0) {
			std::cout << "slave transmission buffer is FULL!\n";
            ret = master.read(data, dataLength);
        } else {
            ret = master.read(data, rwTestLength);
        }

        if(ret == ESP_ERR_TIMEOUT) {
			std::cout << "I2C TIME_OUT\n";
        } else if(ret == ESP_OK) {
			std::cout << "TASK[" << task_idx << "] master read:\n";
            master.printBuffer(master.getRxBuffer(), d_size);
        } else {
			std::cout << esp_err_to_name(ret) << ": Master read slave error, IO not connected...\n";
        }
        ///< ---------------------------------------------------
        int size = 0;
		
		std::cout << "MODIFY_RX +1\n";
		master.modifyRx();
        ///< The slave buffer needs to be filled so the master can read it later
        ret = master.write(master.getRxBuffer(), rwTestLength);
        if(ret == ESP_OK) {
            size = slave.read(slave.getDataBuffer());
        }
        if(ret == ESP_ERR_TIMEOUT) {
			std::cout << "I2C TIME_OUT\n";
        } else if(ret == ESP_OK) {
			std::cout << "Task[" << task_idx << "] master write:\n";
            master.printBuffer(master.getTxBuffer(), rwTestLength);
			std::cout << "Task[" << task_idx << "] slave read: [" << size << "] bytes:\n";
            slave.printBuffer(slave.getDataBuffer(), size);
        } else {
			std::cout << "Task [" << task_idx << "] " << esp_err_to_name(ret) << ": Master write slave error, IO not connected...\n";
        }
        vTaskDelay(( delayTimeBetweenItemsMS * ( task_idx + 1 ) ) / portTICK_RATE_MS);
    }
	//delete data;
}

void app_main() {
    xTaskCreate(twoModesOneESP, "twoModesOneESP", 1024 * 2, (void* ) 1, 10, NULL);
}
