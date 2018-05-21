#include "catch.hpp"
#include "../src/command.hpp"

#include <functional>
#include <utility>

auto command = Command(0x01, 0x2B);

TEST_CASE( "Return command data" ) {
    REQUIRE(command.getCommandData() == std::make_pair(0x01, 0x2B));
}

TEST_CASE( "Set data" ) {
    auto temp = Command(0x2A, 0x2A);
    command.changeCommand(0x2A, 0x2A);
    REQUIRE(temp == command);
}
