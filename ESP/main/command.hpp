#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "LED.hpp"

#include <array>
#include <tuple>
#include <vector>

class Command {
    private:
        std::vector<char> raw;
        uint32_t command;
        uint32_t readBuff;

        enum class instructionType {
            Read        = 0b0001,
            Write       = 0b0010
        };

        auto getType(uint32_t command) noexcept;
        uint16_t getLoc(uint32_t command) noexcept;
        uint8_t getValue(uint32_t command) noexcept;
        void parseRaw() noexcept;
        auto decode();

        void read(uint16_t loc);
        void write(uint16_t loc, uint8_t value);
    public:
        Command(std::vector<char> raw);
        void process(instructionType type);
        void process();
};

#endif // COMMAND_HPP
