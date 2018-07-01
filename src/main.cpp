#include "esp32.hpp"
#include "i2c.hpp"
#include "memory_map.hpp"
#include "twi.hpp"
#include "wrap-hwlib.hpp"

#include <array>

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    constexpr uint32_t twiSpeed = 400000;

    auto bus = I2C::I2C<0x03>();
    auto twi = TWI::TWI<twiSpeed>();

    while (true) {
        auto returns = twi.read<30>(0x28);
        hwlib::wait_ms(500);
    }

    return 0;
}
