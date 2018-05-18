#include "SPI.hpp"

SPI::SPI() {
    //Configure handshake line as output
    //gpio_config(&io_conf);
    //Enable pull-ups on SPI lines so we don't detect rogue pulses when no master is connected.
    //gpio_set_pull_mode(pins::GPIO_MOSI, GPIO_PULLUP_ONLY);
    //gpio_set_pull_mode(pins::GPIO_SCLK, GPIO_PULLUP_ONLY);
    //gpio_set_pull_mode(pins::GPIO_CS, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(static_cast<gpio_num_t>(12), GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(static_cast<gpio_num_t>(13), GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(static_cast<gpio_num_t>(14), GPIO_PULLUP_ONLY);

    //Initialize SPI slave interface
    ret=spi_slave_initialize(HSPI_HOST, &buscfg, &slvcfg, 1);
    assert(ret==ESP_OK);
};

bool SPI::SPIInit() {
    try {
        std::memset(recvBuffer, 0x00, sizeof recvBuffer);
        std::memset(sendBuffer, 0x00, sizeof sendBuffer);

        transaction.length=128;
        transaction.tx_buffer=sendBuffer;
        transaction.rx_buffer=recvBuffer;
    } catch (...) {
        return false;
    }

    printf("Initialized SPI Slave bus");
    return true;
};

void SPI::waitForTransaction() {
    ret = spi_slave_transmit(HSPI_HOST, &transaction, portMAX_DELAY);
}

void SPI::printRecv() {
    //printf("Received: %x\n", recvBuffer[0]);
    //printf("Received: %x\n", recvBuffer[1]);
    for(int i = 0; i < sizeof(recvBuffer); ++i) {
        printf("%x", recvBuffer[i]);
    }
    auto led = LED();
    led.blinkInfinitly(500);
}
