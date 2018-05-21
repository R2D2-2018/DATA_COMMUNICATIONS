#include "command.hpp"

Command::Command(uint8_t type, uint8_t location):
    type(type),
    location(location)
{}

std::pair<uint8_t, uint8_t> Command::getCommandData() {
    return std::make_pair(type, location);
}

void Command::setData(std::array<uint8_t, 2> sendData) {
    data[0] = std::get<0>(sendData);
    data[1] = std::get<1>(sendData);
}

void Command::changeCommand(uint8_t type, uint8_t location) {
    return;
}

void Command::sendCommand() {
    auto bus = due::spi_bus_due();
    uint8_t writeOp[2] = {type, location};
    uint8_t writeOp2[2] = {data[0], data[1]};

    bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp), (writeOp), nullptr);
    hwlib::wait_ms(500);
    bus.write_and_read(hwlib::pin_out_dummy, sizeof(writeOp2), (writeOp2), nullptr);
    hwlib::wait_ms(500);
}
