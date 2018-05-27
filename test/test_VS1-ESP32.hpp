#include "../src/ESP32.hpp"
#include "catch.hpp"

#include <typeinfo>

TEST_CASE("ESP32 instance is of type ESP32", "[Type]") {
    REQUIRE(typeid(esp32).name() == typeid(ESP32).name());
}
