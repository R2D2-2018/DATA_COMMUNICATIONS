#include "Master_slave_settings.hpp"
#include "I2C_ESP.hpp"

MasterSlaveSettings::MasterSlaveSettings(){};

///< Tasks which performs tests					Example:
///< 1. Slave buffer is filled with data	--> [1,2,3]
///< 2. Master reads data from slave		--> [1,2,3]
///< 2. Master writes data to slave			--> [7,7,7]
///< 3. Master reads data from slave		--> [7,7,7]
void MasterSlaveSettings::masterAndSlave(void *taskID) {
    i2c_port_t slavePortNum = i2c_port_t::I2C_NUM_0;   ///< Slave port number
    gpio_num_t slaveSDA     = gpio_num_t::GPIO_NUM_25; ///< GPIO number for slave dataBuffer
    gpio_num_t slaveSCL     = gpio_num_t::GPIO_NUM_26; ///< GPIO number for slave CLK

    i2c_port_t masterPortNum = i2c_port_t::I2C_NUM_1;   ///< Master port number
    gpio_num_t masterSDA     = gpio_num_t::GPIO_NUM_18; ///< GPIO number for master dataBuffer
    gpio_num_t masterSCL     = gpio_num_t::GPIO_NUM_19; ///< GPIO number for master CLK

    I2cEsp slave(slaveSDA, slaveSCL, slavePortNum);
    I2cEsp master(masterSDA, masterSCL, masterPortNum, true);

    int i = 0;
    int ret;
    uint32_t task_idx = (uint32_t)taskID;

    int dataLength = 64;

    uint8_t data[dataLength];

    int count = 0;

    for (i = 0; i < dataLength; i++) {
        data[i] = i;
    }
    size_t d_size = slave.write(data);

    if (d_size == 0) {
        std::cout << "slave transmission buffer is FULL!\n";
        ret = master.read();
    } else {
        ret = master.read();
    }

    std::cout << "TASK[" << task_idx << "] Slave buffer data:\n";
    slave.printBuffer(slave.getDataBuffer(), d_size);

    while (1) {
        std::cout << "==================\n";
        std::cout << "test count: " << count++ << "\n";
        std::cout << "==================\n";

        d_size = slave.write(slave.getDataBuffer());

        if (d_size == 0) {
            std::cout << "slave transmission buffer is FULL!\n";
            ret = master.read();
        } else {
            ret = master.read();
        }

        if (ret == ESP_ERR_TIMEOUT) {
            std::cout << "I2C TIME_OUT\n";
        } else if (ret == ESP_OK) {
            std::cout << "TASK[" << task_idx << "] master read:\n";
            master.printBuffer(master.getRxBuffer(), d_size);
        } else {
            std::cout << esp_err_to_name(ret) << ": Master read slave error, IO not connected...\n";
        }

        int size = 0;

        std::cout << "MODIFY_RX +1\n";
        master.modifyRx();

        ret = master.write(master.getRxBuffer(), master.getRwBufferLength());
        if (ret == ESP_OK) {
            size = slave.read();
        }
        if (ret == ESP_ERR_TIMEOUT) {
            std::cout << "I2C TIME_OUT\n";
        } else if (ret == ESP_OK) {
            std::cout << "Task[" << task_idx << "] master write:\n";
            master.printBuffer(master.getTxBuffer(), master.getRwBufferLength());
            std::cout << "Task[" << task_idx << "] slave read: [" << size << "] bytes:\n";
            slave.printBuffer(slave.getDataBuffer(), size);
        } else {
            std::cout << "Task [" << task_idx << "] " << esp_err_to_name(ret)
                      << ": Master write slave error, IO not connected...\n";
        }
        vTaskDelay((delayTimeBetweenItemsMS * (task_idx + 1)) / portTICK_RATE_MS);
    }
}

void MasterSlaveSettings::master(void *taskID) {
    i2c_port_t masterPortNum = i2c_port_t::I2C_NUM_1;   ///< Master port number
    gpio_num_t masterSDA     = gpio_num_t::GPIO_NUM_18; ///< GPIO number for master dataBuffer
    gpio_num_t masterSCL     = gpio_num_t::GPIO_NUM_19; ///< GPIO number for master CLK

    I2cEsp master(masterSDA, masterSCL, masterPortNum, true);

    int ret;
    uint32_t task_idx = (uint32_t)taskID;

    int dataLength = 64;
    uint8_t data[dataLength];

    for (int i = 0; i < dataLength; i++) {
        data[i] = i;
    }

    int count = 0;

    while (1) {
        std::cout << "==================\n";
        std::cout << "test count: " << count++ << "\n";
        std::cout << "==================\n";

        ret = master.write(data, master.getRwBufferLength());

        if (ret == ESP_ERR_TIMEOUT) {
            std::cout << "I2C TIME_OUT\n";
        } else if (ret == ESP_OK) {
            std::cout << "Task[" << task_idx << "] master write:\n";
            master.printBuffer(master.getTxBuffer(), master.getRwBufferLength());
        } else {
            std::cout << "Task [" << task_idx << "] " << esp_err_to_name(ret)
                      << ": Master write slave error, IO not connected...\n";
        }

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
}

void MasterSlaveSettings::slave(void *taskID) {

    i2c_port_t slavePortNum = i2c_port_t::I2C_NUM_0;   ///< Slave port number
    gpio_num_t slaveSDA     = gpio_num_t::GPIO_NUM_25; ///< GPIO number for slave dataBuffer
    gpio_num_t slaveSCL     = gpio_num_t::GPIO_NUM_26; ///< GPIO number for slave CLK

    I2cEsp slave(slaveSDA, slaveSCL, slavePortNum);

    uint32_t task_idx = (uint32_t)taskID;

    int count = 0;
    int size  = 0;

    size_t d_size = 0;

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

        std::cout << "MODIFYING DATA...\n";
        slave.modifyData();

        d_size = slave.write(slave.getDataBuffer());

        if (d_size == 0) {
            std::cout << "slave transmission buffer is FULL!\n";
        } else {

            std::cout << "TASK[" << task_idx << "] Slave write:\n";
            slave.printBuffer(slave.getDataBuffer(), d_size);
        }

        vTaskDelay((delayTimeBetweenItemsMS * (task_idx + 1)) / portTICK_RATE_MS);
    }
}