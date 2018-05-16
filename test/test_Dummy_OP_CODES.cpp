#include "catch.hpp"
#include "../src/ESP32.hpp"

// esp32 was declared in test_ESP32.cpp

TEST_CASE( "readRegister function in ESP32 class returns address" ){
	REQUIRE(esp32.readRegister(0) == 0);
	REQUIRE(esp32.readRegister(1) == 1);
	REQUIRE(esp32.readRegister(-1) == -1);
}

TEST_CASE( "readBuffer function in ESP32 class returns 0" ){
	REQUIRE(esp32.readBuffer() == 0);	
}

