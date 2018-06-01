#include "../src/I2C.hpp"
#include "catch.hpp"

#include <array>

auto bus = I2C::I2C<0x03>();

TEST_CASE("Read returns address", "[Read]") {
    const uint8_t addr = 0x28;
    REQUIRE(bus.read(addr) == static_cast<uint8_t>(0x28));
}

TEST_CASE("Read returns std::array", "[Read]") {
    std::array<uint8_t, 4> arr = {0};

    auto retArr = bus.read<4>(static_cast<uint8_t>(0x28));
    REQUIRE(retArr == arr);
}

TEST_CASE("Write returns empty array", "[Write]") {
    std::array<uint8_t, 4> arr = {0};
    bus.write<4>(0x28, arr);
}

TEST_CASE("Object contains device address", "[Address]") {
    REQUIRE(bus.getDeviceAddress() == 0x03);
}
