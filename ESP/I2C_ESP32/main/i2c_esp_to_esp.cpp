#include "i2c_esp_to_esp.hpp"

i2cEsp::i2cEsp(const gpio_num_t &sda, const gpio_num_t &scl, const i2c_port_t &portNum, bool isMaster)
    : sda(sda), scl(scl), portNum(portNum), isMaster(isMaster) {

    i2c_config_t config;

    config.sda_io_num    = sda;
    config.sda_pullup_en = GPIO_PULLUP_ENABLE;
    config.scl_io_num    = scl;
    config.scl_pullup_en = GPIO_PULLUP_ENABLE;

    if (isMaster) {
        txBufferLength = 0; ///< Master transmission buffer size
        rxBufferLength = 0; ///< Master receiving buffer size

        config.mode             = I2C_MODE_MASTER;
        config.master.clk_speed = masterClockFrequency;
    } else {
        txBufferLength = 2 * dataLength; ///< Slave transmission buffer size
        rxBufferLength = 2 * dataLength; ///< Slave receiving buffer size

        config.mode                = I2C_MODE_SLAVE;
        config.slave.addr_10bit_en = 0;
        config.slave.slave_addr    = slaveAddress;
    }

    i2c_param_config(portNum, &config);
    i2c_driver_install(portNum, config.mode, rxBufferLength, txBufferLength, 0);
}

i2cEsp::~i2cEsp() {
    delete dataBuffer;
    delete txBuffer;
    delete rxBuffer;
}

esp_err_t i2cEsp::read() {
    if (isMaster) {
        i2c_cmd_handle_t link = i2c_cmd_link_create();
        i2c_master_start(link);
        i2c_master_write_byte(link, (slaveAddress << 1) | readBit, checkAck);

        i2c_master_read(link, rxBuffer, rwBufferLength - 1, masterAck);

        i2c_master_read_byte(link, rxBuffer + rwBufferLength - 1, masterNack);
        i2c_master_stop(link);
        esp_err_t ret = i2c_master_cmd_begin(portNum, link, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link);

        return ret;
    } else {
        int size = i2c_slave_read_buffer(portNum, dataBuffer, rwBufferLength, 1000 / portTICK_RATE_MS);
        return size;
    }
}

esp_err_t i2cEsp::write(uint8_t *txBuffer, size_t size) {

    if (isMaster) {
        for (int i = 0; i < size; ++i) {
            this->txBuffer[i] = txBuffer[i];
        }

        i2c_cmd_handle_t link = i2c_cmd_link_create();
        i2c_master_start(link);
        i2c_master_write_byte(link, (slaveAddress << 1) | writeBit, checkAck);
        i2c_master_write(link, txBuffer, size, checkAck);
        i2c_master_stop(link);
        esp_err_t ret = i2c_master_cmd_begin(portNum, link, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link);

        return ret;
    } else {
        for (int i = 0; i < size; ++i) {
            dataBuffer[i] = txBuffer[i];
        }
        size_t size = i2c_slave_write_buffer(portNum, dataBuffer, rwBufferLength, 1000 / portTICK_RATE_MS);
        return size;
    }
}

void i2cEsp::printBuffer(uint8_t *buffer, int len) {
    std::cout << std::hex;
    int i;
    for (i = 0; i < len; i++) {
        std::cout << int(buffer[i]) << ' ';
        if ((i + 1) % 16 == 0) {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
    std::cout << std::dec;
}

void i2cEsp::modifyData() {
    for (int i = 0; i < rwBufferLength; ++i) {
        dataBuffer[i] += 1;
    }
}
void i2cEsp::modifyRx() {
    for (int i = 0; i < rwBufferLength; ++i) {
        rxBuffer[i] += 1;
    }
}
void i2cEsp::modifyTx() {
    for (int i = 0; i < rwBufferLength; ++i) {
        txBuffer[i] += 1;
    }
}

uint8_t *i2cEsp::getDataBuffer() {
    return dataBuffer;
}
uint8_t *i2cEsp::getRxBuffer() {
    return rxBuffer;
}
uint8_t *i2cEsp::getTxBuffer() {
    return txBuffer;
}

int i2cEsp::getRwBufferLength() {
    return rwBufferLength;
}
