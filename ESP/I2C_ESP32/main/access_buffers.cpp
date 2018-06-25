#include "access_buffers.hpp"

AccessBuffers::AccessBuffers(){};

///< Tasks which performs tests					Example:
///< 1. Slave buffer is filled with data	--> [1,2,3]
///< 2. Master reads data from slave		--> [1,2,3]
///< 2. Master writes data to slave			--> [7,7,7]
///< 3. Master reads data from slave		--> [7,7,7]

uint8_t * AccessBuffers::masterRead(void *taskID){
    i2c_port_t masterPortNum = i2c_port_t::I2C_NUM_1;   ///< Master port number
    gpio_num_t masterSDA     = gpio_num_t::GPIO_NUM_18; ///< GPIO number for master dataBuffer
    gpio_num_t masterSCL     = gpio_num_t::GPIO_NUM_19; ///< GPIO number for master CLK

    I2cEsp master(masterSDA, masterSCL, masterPortNum, true);

    int ret;

    ret = master.read();

    if(ret == ESP_OK) {
        return master.getRxBuffer();
    } else {
        int bufferLength = 64; //just an random size
        uint8_t buffer[bufferLength];
        getDefaultArray(buffer, bufferLength);
        return buffer;
    }
};

bool AccessBuffers::masterWrite(uint8_t *buffer, int bufferLength){
    i2c_port_t masterPortNum = i2c_port_t::I2C_NUM_1;   ///< Master port number
    gpio_num_t masterSDA     = gpio_num_t::GPIO_NUM_18; ///< GPIO number for master dataBuffer
    gpio_num_t masterSCL     = gpio_num_t::GPIO_NUM_19; ///< GPIO number for master CLK

    I2cEsp master(masterSDA, masterSCL, masterPortNum, true);

    int ret;
    int x = master.getRwBufferLength();

    if (bufferLength > x){
        //if size of parameter buffer to big
        return 0;
    }

    ret = master.write(buffer, bufferLength);

    if (ret == ESP_ERR_TIMEOUT) {
        // if I2C TIME_OUT is returned form master.write()
        return 0;
    } else if (ret != ESP_OK) {
        // io is probebly not connected
        return 0;
    } 
    return 1;
};

void AccessBuffers::masterPrintBuffer(void *taskID){
    i2c_port_t masterPortNum = i2c_port_t::I2C_NUM_1;   ///< Master port number
    gpio_num_t masterSDA     = gpio_num_t::GPIO_NUM_18; ///< GPIO number for master dataBuffer
    gpio_num_t masterSCL     = gpio_num_t::GPIO_NUM_19; ///< GPIO number for master CLK

    I2cEsp master(masterSDA, masterSCL, masterPortNum, true);

    int ret;
    uint32_t task_idx = (uint32_t)taskID;

    int count = 0;  

    while (1) {
        std::cout << "==================\n";
        std::cout << "test count: " << count++ << "\n";
        std::cout << "==================\n";

        ret = master.read();

        if (ret == ESP_ERR_TIMEOUT) {
            std::cout << "I2C TIME_OUT\n";
        } else if (ret == ESP_OK) {
            std::cout << "TASK[" << task_idx << "] master read:\n";
            master.printBuffer(master.getRxBuffer(), master.getRwBufferLength());
        } else {
            std::cout << esp_err_to_name(ret) << ": Master read slave error, IO not connected...\n";
        }

        vTaskDelay((delayTimeBetweenItemsMS * (task_idx + 1)) / portTICK_RATE_MS);
    }
};

uint8_t * AccessBuffers::slaveRead(void *taskID){
    i2c_port_t slavePortNum = i2c_port_t::I2C_NUM_0;   ///< Slave port number
    gpio_num_t slaveSDA     = gpio_num_t::GPIO_NUM_25; ///< GPIO number for slave dataBuffer
    gpio_num_t slaveSCL     = gpio_num_t::GPIO_NUM_26; ///< GPIO number for slave CLK

    I2cEsp slave(slaveSDA, slaveSCL, slavePortNum);

    uint32_t task_idx = (uint32_t)taskID;

    int size  = 0;

    size = slave.read();

    if (size == ESP_ERR_TIMEOUT) {
        int bufferLength = 64; //just an random size
        uint8_t buffer[bufferLength];
        getDefaultArray(buffer, bufferLength);
        return buffer;
    } else {
        return slave.getDataBuffer();
    }
    vTaskDelay((delayTimeBetweenItemsMS * (task_idx + 1)) / portTICK_RATE_MS);
}

bool AccessBuffers::slaveWrite(uint8_t *buffer, int bufferLength){
    i2c_port_t slavePortNum = i2c_port_t::I2C_NUM_0;   ///< Slave port number
    gpio_num_t slaveSDA     = gpio_num_t::GPIO_NUM_25; ///< GPIO number for slave dataBuffer
    gpio_num_t slaveSCL     = gpio_num_t::GPIO_NUM_26; ///< GPIO number for slave CLK

    I2cEsp slave(slaveSDA, slaveSCL, slavePortNum);

    size_t d_size = 0;
    int x = slave.getRwBufferLength();

    if (bufferLength > x){
        //if size of parameter buffer to big
        return 0;
    }

    while (1) {
        d_size = slave.write(slave.getDataBuffer());

        if (d_size == 0) {
            //slave transmition buffer is full
            return 0;
        } else {
            slave.write(buffer, bufferLength);
            return 1;
        }

    }
}

void AccessBuffers::slavePrintBuffer(void *taskID){
    i2c_port_t slavePortNum = i2c_port_t::I2C_NUM_0;   ///< Slave port number
    gpio_num_t slaveSDA     = gpio_num_t::GPIO_NUM_25; ///< GPIO number for slave dataBuffer
    gpio_num_t slaveSCL     = gpio_num_t::GPIO_NUM_26; ///< GPIO number for slave CLK

    I2cEsp slave(slaveSDA, slaveSCL, slavePortNum);

    uint32_t task_idx = (uint32_t)taskID;

    int count = 0;
    int size  = 0;

    while (1) {
        std::cout << "==================\n";
        std::cout << "test count: " << count++ << "\n";
        std::cout << "==================\n";

        size = slave.read();

        if (size == ESP_ERR_TIMEOUT) {
            std::cout << "I2C TIME_OUT\n";
        } else {
            std::cout << "Task[" << task_idx << "] slave read: [" << size << "] bytes:\n";
            slave.printBuffer(slave.getDataBuffer(), size);
        }
        vTaskDelay((delayTimeBetweenItemsMS * (task_idx + 1)) / portTICK_RATE_MS);
    }
}

void AccessBuffers::getDefaultArray(uint8_t *buffer, int bufferLength) {
    for (int i = 0; i < bufferLength; i++) {
        buffer[i] = i;
    }
}