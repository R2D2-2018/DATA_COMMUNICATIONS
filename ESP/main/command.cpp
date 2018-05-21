#include "command.hpp"

Command::Command(std::vector<char> raw):
    raw(raw)
{
    parseRaw();
    printf("Command excepted\n");
};

auto Command::getType(uint32_t command) noexcept {
    return static_cast<instructionType>((command >> 24) & 0xFF);
    /*
    switch (0b1111 & (command >> 24)) {
        case instructionType::Read: return 
    */
}

void Command::parseRaw() noexcept {
    std::array<uint8_t, 4> temp;
    std::get<0>(temp) = raw[0];
    std::get<1>(temp) = raw[1];
    std::get<2>(temp) = raw[2];
    std::get<3>(temp) = raw[3];
    command = (std::get<0>(temp) << 24) | (std::get<1>(temp) << 16) |
              (std::get<2>(temp) << 8)  | (std::get<3>(temp));
    printf("Full command: %x\n", command);
}

void Command::process() {
    switch (getType(command)) {
        case instructionType::Read: read(getLoc(command)); break;
        case instructionType::Write: write(getLoc(command), getValue(command)); break;
        default: printf("invalid type\n"); break;
    }
}

uint16_t Command::getLoc(uint32_t command) noexcept {
    auto temp = (((command >> 16) & 0xFF) | ((command >> 8) & 0xFF));
    return static_cast<uint16_t>(temp);
}

uint8_t Command::getValue(uint32_t command) noexcept {
    return static_cast<uint8_t>(command & 0xFF);
}

void Command::read(uint16_t loc) {
    auto led = LED();
    led.blinkInfinitly(static_cast<int>(loc));
}

void Command::write(uint16_t loc, uint8_t value) {
    auto led = LED();
    led.blinkInfinitly(static_cast<int>(loc));
}
