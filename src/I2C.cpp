#include "I2C.hpp"

I2C::I2C::I2C() {
}

auto I2C::I2C::read(const uint8_t address) -> uint8_t {
    return address;
}

template <std::size_t length>
auto I2C::I2C::read(const uint8_t address) -> std::array<uint8_t, length> {
    std::array<uint8_t, length> retArray = {0};
    return retArray;
}

template <std::size_t length>
auto I2C::I2C::write(const uint8_t address, std::array<uint8_t, length> &buffer) -> void {
    return;
}
