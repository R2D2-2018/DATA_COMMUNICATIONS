#ifndef I2C_HPP
#define I2C_HPP

#include "driver/i2c.h"

class I2C {
    private:
        enum class settings {
            I2C_EXAMPLE_SLAVE_SCL_IO = 22,
            I2C_EXAMPLE_SLAVE_SDA_IO = 21,
            I2C_EXAMPLE_SLAVE_NUM = I2C_NUM_0,
            I2C_EXAMPLE_SLAVE_TX_BUF_LEN = (2*512),
            I2C_EXAMPLE_SLAVE_RX_BUF_LEN = (2*512),
            ESP_SLAVE_ADDR = 0x28
        };

        i2c_config_t conf_slave;
    
        void I2CSlaveInit() noexcept;
        
    public:
        I2C();
};

#endif // I2C_HPP
