#ifndef SPI_HPP
#define SPI_HPP

#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "soc/rtc_cntl_reg.h"
#include "rom/cache.h"
#include "driver/spi_slave.h"
#include "esp_log.h"
#include "esp_spi_flash.h"

class SPI {
    private:
        enum pins : uint8_t {
            GPIO_MOSI = 12,
            GPIO_MISO = 13,
            GPIO_SCLK = 15,
            GPIO_CS = 14,
        };

        esp_err_t ret;

        //Configuration for the SPI bus
        spi_bus_config_t buscfg={
            .mosi_io_num=pins::GPIO_MOSI,
            .miso_io_num=pins::GPIO_MISO,
            .sclk_io_num=pins::GPIO_SCLK,
            .quadwp_io_num=-1,
            .quadhd_io_num=-1,
            .max_transfer_sz=0,
            .flags=0,
        };

        //Configuration for the SPI slave interface
        spi_slave_interface_config_t slvcfg={
            .spics_io_num=pins::GPIO_CS,
            .flags=0,
            .queue_size=3,
            .mode=0,
            .post_setup_cb=nullptr,
            .post_trans_cb=nullptr,
        };

    public:
        SPI();

        
};

#endif // SPI_HPP