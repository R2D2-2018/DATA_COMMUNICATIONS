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

#include "LED.hpp"

#include <cstring>

#include <array>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

class SPI {
    private:
        enum pins : uint8_t {
            GPIO_MOSI = 12, ///< GPIO pin 12 Master-out-slave-in
            GPIO_MISO = 13, ///< GPIO pin 13 Master-in-Slave-out
            GPIO_SCLK = 15, ///< GPIO pin 15 Clock
            GPIO_CS = 14,   ///< GPIO pin 14 Chip-select
        };

        esp_err_t ret; ///< ESP error return structure

        ///< Configuration for the SPI bus
        spi_bus_config_t buscfg={
            .mosi_io_num=pins::GPIO_MOSI,
            .miso_io_num=pins::GPIO_MISO,
            .sclk_io_num=pins::GPIO_SCLK,
            .quadwp_io_num=-1,
            .quadhd_io_num=-1,
            .max_transfer_sz=0,
            .flags=0,
        };

        ///< Configuration for the SPI slave interface
        spi_slave_interface_config_t slvcfg={
            .spics_io_num=pins::GPIO_CS,
            .flags=0,
            .queue_size=3,
            .mode=0,
            .post_setup_cb=nullptr,
            .post_trans_cb=nullptr,
        };

        char recvBuffer[16] = ""; ///< Receive buffer for the SPI slave
        char sendBuffer[16] = ""; ///< Sending buffer for the SPI slave
        
    public:
        /**
         * @brief       Constructor for the SPI Slave
         *
         * Constructs the SPI slave object.
         */
        SPI();

        /**
         * @brief       Initializes the SPI bus
         * 
         * Initialises the SPI bus as a slave.
         *
         * @returns     Bool which will be true upon good execution.
         */
        bool SPIInit();

        /**
         * @brief       Puts ESP on hold until the a transaction has taken place.
         *
         * The ESP32 will be waiting for a SPI transaction to take place.
         */
        void waitForTransaction();
        /**
         * @brief       Print the receive and send buffer.
         *
         * Function prints the received and send buffer to the console.
         * Function also puts the first 2 bytes into the extraction buffer.
         *
         * @param[in]   destBuffer      Destination buffer for the first 2 bytes.
         */
        void printRecv(std::vector<char>& destBuffer);
};

#endif // SPI_HPP
