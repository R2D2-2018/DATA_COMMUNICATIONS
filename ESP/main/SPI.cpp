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
    /*
    try {
        std::memset(recvBuffer, 0x41, sizeof(recvBuffer));
        std::memset(sendBuffer, 0x00, sizeof(sendBuffer));

        transaction.length=4;
        transaction.tx_buffer=sendBuffer;
        transaction.rx_buffer=recvBuffer;
    } catch (...) {
        return false;
    }

    printf("Initialized SPI Slave bus\n");
    */
    return true;
};

void SPI::waitForTransaction() {
    spi_slave_transaction_t transaction;
    spi_slave_transaction_t* out;
    std::memset(recvBuffer, 0x41, sizeof(recvBuffer));
    std::memset(sendBuffer, 0x00, sizeof(sendBuffer));
    std::memset(&transaction, 0, sizeof(transaction));
    //SPIInit();

    transaction.length=8*4;
    transaction.tx_buffer=sendBuffer;
    transaction.rx_buffer=recvBuffer;

    ret = spi_slave_transmit(HSPI_HOST, &transaction, portMAX_DELAY);
    if(ret != ESP_OK) {
        printf("Look here");
    }
    printf("Transaction received\n");
}

void SPI::printRecv() {
    //printf("Received: %x\n", recvBuffer[0]);
    //printf("Received: %x\n", recvBuffer[1]);
    for(int i = 0; i < sizeof(recvBuffer); ++i) {
        printf("%x", recvBuffer[i]);
    }
    printf("\n");
    for(int i = 0; i < sizeof(sendBuffer); ++i) {
        printf("%x", sendBuffer[i]);
    }
    printf("\n");
    auto led = LED();
    //led.blinkInfinitly(500);
}
