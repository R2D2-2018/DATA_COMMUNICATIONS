#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "SPI.hpp"
#include "wrap-hwlib.hpp"

#include <array>
#include <functional>
#include <utility>

class Command {
    private:
        uint8_t type;
        uint8_t location;
        std::array<uint8_t, 2> data = {0x00, 0x00};
    public:
        Command(uint8_t type, uint8_t location);

        std::pair<uint8_t, uint8_t> getCommandData();
        void setData(std::array<uint8_t, 2> sendData);
        void changeCommand(uint8_t type, uint8_t location);
        void sendCommand();
};

#endif // COMMAND_HPP
