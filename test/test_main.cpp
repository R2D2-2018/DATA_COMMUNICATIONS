#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/ESP32.hpp"

ESP32 test_ESP32;

TEST_CASE( "Example Test Case" ) {
    REQUIRE(10 == 10);
}

TEST_CASE( "Return input" ) {
    REQUIRE(test_ESP32.readRegister(0) == 0);
    REQUIRE(test_ESP32.readRegister(1) == 1);
    REQUIRE(test_ESP32.readRegister(5) == 5);
    REQUIRE(test_ESP32.readRegister(-1) == -1);
}

TEST_CASE( "Return 0" ) {
    REQUIRE(test_ESP32.readBuffer() == 0);
}