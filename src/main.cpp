#include "ESP32.hpp"
#include "I2C.hpp"
#include "memory_map.hpp"
#include "wrap-hwlib.hpp"

#include <array>

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(2500);
    /*

    auto bus = due::spi_bus_due();
    //uint8_t writeOp[4] = {0xA2, 0xA1, 0xA8, 0x03};
    uint8_t writeOp[] = {0xA2, 0xA1};
    uint8_t writeOp2[] = {0x2A, 0x1A};
    uint8_t writeOp3[] = {0x2B, 0x1B};
    uint8_t writeOp4[] = {0x2C, 0x1C};

    uint8_t command[] = {0x01, 0xFF, 0xFF, 0xFF};

    while (true) {
        bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp), writeOp, nullptr);
        hwlib::wait_ms(500);
    }
    //bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp), writeOp, nullptr);
    //hwlib::wait_ms(500);
    //bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp), writeOp2, nullptr);
    //hwlib::wait_ms(500);
    //bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp), writeOp3, nullptr);
    //hwlib::wait_ms(500);
    //bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp), writeOp4, nullptr);
    //hwlib::wait_ms(500);

    uint8_t op[2] = {command[0], command[1]};
    bus.write_and_read(hwlib::pin_out_dummy, sizeof(op), op, nullptr);
    hwlib::wait_ms(500);
    uint8_t op2[2] = {command[2], command[3]};
    bus.write_and_read(hwlib::pin_out_dummy, sizeof(op), op2, nullptr);
    hwlib::wait_ms(500);

    //auto esp = ESP32();
    //std::array<uint8_t, 2> data = {0x02, 0x03};

    //esp.writeRegister(0x01, data);
    */

    // hwlib::cout << "hello world" << hwlib::endl;

    auto bus = I2C::I2C();

    std::array<uint8_t, 4> arr = {0};
    // bus.write<4>(0x28, arr);

    return 0;
}
