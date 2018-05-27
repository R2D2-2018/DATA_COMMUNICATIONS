#include "catch.hpp"
#include "ESP32.hpp"

ESP32 esp32;

TEST_CASE( "Return input" ) {
    REQUIRE(esp32.readRegister(0) == 0);
    REQUIRE(esp32.readRegister(1) == 1);
    REQUIRE(esp32.readRegister(5) == 5);
    REQUIRE(esp32.readRegister(-1) == -1);
}

TEST_CASE( "Return 0" ) {
    REQUIRE(esp32.readBuffer() == 0);
}
