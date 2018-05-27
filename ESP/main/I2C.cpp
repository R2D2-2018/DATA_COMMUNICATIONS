#include "I2C.hpp"

I2C::I2C() {
    I2CSlaveInit();
}

void I2C::I2CSlaveInit() noexcept {
    conf_slave.sda_io_num       = settings::I2C_SLAVE_SDA_IO;
    conf_slave.sda_pullup_en    = settings::GPIO_PULLUP_ENABLE;
    conf_slave.scl_io_num       = settings::I2C_SLAVE_SCL_IO;
    conf_slave.scl_pullup_en    = settings::GPIO_PULLUP_ENABLE;
    conf_slave.mode             = settings::I2C_MODE_SLAVE;
    conf_slave.slave.addr_10bit_en = 0;
    conf_slave.slave.slave_addr = settings::ESP_SLAVE_ADDR;
    i2c_param_config(i2c_slave_port, &conf_slave);
    i2c_driver_install(i2c_slave_port, conf_slave.mode,
                       settings::I2C_SLAVE_RX_BUF_LEN,
                       settings::I2C_SLAVE_TX_BUF_LEN, 0);
}

uint16_t I2C::waitForWrite() noexcept {
    auto retSize = i2c_slave_read_buffer(settings::I2C_SLAVE_NUM, rxBuffer, 4, 1000/portTICK_RATE_MS);
    return retSize;
}
