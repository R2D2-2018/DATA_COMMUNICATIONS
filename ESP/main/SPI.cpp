#include "SPI.hpp"

SPI::SPI() {
    //Configure handshake line as output
    //gpio_config(&io_conf);
    //Enable pull-ups on SPI lines so we don't detect rogue pulses when no master is connected.
    gpio_set_pull_mode(pins::GPIO_MOSI, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(pins::GPIO_SCLK, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(pins::GPIO_CS, GPIO_PULLUP_ONLY);

    //Initialize SPI slave interface
    ret=spi_slave_initialize(HSPI_HOST, &buscfg, &slvcfg, 1);
    assert(ret==ESP_OK);
};
