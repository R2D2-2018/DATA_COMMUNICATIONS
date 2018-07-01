#include "../src/esp32.hpp"
#include "catch.hpp"
#include "test_ESP32.hpp"

TEST_CASE("readRegister function in ESP32 class returns address", "[Data_IO]") {
    REQUIRE(espTest.readRegister(0) == 0);
    REQUIRE(espTest.readRegister(1) == 1);
    REQUIRE(espTest.readRegister(-1) == -1);
}

TEST_CASE("readBuffer function in ESP32 class returns 0", "[Data_IO]") {
    REQUIRE(espTest.readBuffer() == 0);
}
