#include "catch.hpp"

TEST_CASE( "Return input" ) {
    REQUIRE(ESP32::readRegister(0) == 0);
    REQUIRE(ESP32::readRegister(1) == 1);
    REQUIRE(ESP32::readRegister(5) == 5);
    REQUIRE(ESP32::readRegister(-1) == -1);
}

TEST_CASE( "Return 0" ) {
    REQUIRE(ESP32::readBuffer() == 0);
}