#include "catch.hpp"
#include "../src/ESP32.hpp"

#include <typeinfo>

ESP32 esp32;

TEST_CASE( "ESP32 instance is of type ESP32" ){
	REQUIRE(typeid(esp32).name() == typeid(ESP32).name());
}


