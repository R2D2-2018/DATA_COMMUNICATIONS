#include "wrap-hwlib.hpp"
#include "ESP32.hpp"
#include "SPI.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
	
    hwlib::wait_ms(2500);

    auto bus = due::spi_bus_due();
    uint8_t writeOp[4] = {0xA2, 0xA1, 0xA8, 0x03};

    while (true) {
        bus.write_and_read(hwlib::pin_out_dummy, 4, writeOp, nullptr);    
        hwlib::wait_ms(500);
    }
	
    return 0;
}
