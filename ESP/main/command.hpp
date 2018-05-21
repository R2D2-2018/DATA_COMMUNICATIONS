#ifndef COMMAND_HPP
#define COMMAND_HPP

/**
 * @file        command.hpp
 * @brief       Command processor and executioner.
 * @author      Niels de Waal
 * @license     MIT
 */

#include "LED.hpp"

#include <array>
#include <tuple>
#include <vector>

class Command {
    private:
        std::vector<char> raw; ///< Raw data for a command.
        uint32_t command; ///< Formated command.
        uint32_t readBuff; ///< Buffer for a read command.

        enum class instructionType {
            Read        = 0b0001, ///< Read command.
            Write       = 0b0010  ///< Write command.
        };

        /**
         * @brief       Function which returns the type of a command.
         *
         * Function returns the command type.
         * Can be either Read of Write.
         *
         * @param[in]   command Full command data.
         * @return      Returns either Read or Write instructionType.
         */
        auto getType(uint32_t command) noexcept;
        /**
         * @brief       Function to get the address stored in a command.
         *
         * Function which returns the address stored in a command.
         *
         * @param[in]   command Full command data.
         * @return      16-bit value of the command address.
         */
        uint16_t getLoc(uint32_t command) noexcept;
        /**
         * @brief       Function to get the value stored in a command.
         *
         * Function which returns the data stored in a command.
         *
         * @param[in]   command Full command data.
         * @return      8-bit value of the data stored in a command.
         */
        uint8_t getValue(uint32_t command) noexcept;
        /**
         * @brief       Function which parses the raw data into a command.
         *
         * This function takes the raw data that has been transfered to the ESP32 
         * and parses it into a command.
         */
        void parseRaw() noexcept;
        /**
         * @brief       Function to decode a parsed command.
         *
         * TODO
         * Function takes the command data and decodes it into a task which the ESP32 can execute.
         *
         * @return
         */
        auto decode();

        /**
         * @brief       Read a value from a specified location.
         *
         * Function reads the value stored at a specified location.
         * Value stored in the readBuff array.
         *
         * @param[in]   loc     16-bit location.
         */
        void read(uint16_t loc);
        /**
         * @brief       Write a value to a location
         *
         * Function writes the value to loc.
         *
         * @param[in]   loc     16-bit location to write to.
         * @param[in]   value   Value to write to the location.
         */
        void write(uint16_t loc, uint8_t value);
    public:
        /**
         * @brief       Command object constructor
         *
         * Constructor for the command object.
         *
         * @param[in]   raw     vector containing the raw bytes received.
         */
        Command(std::vector<char> raw);
        /**
         * @brief       Process the instruction according to the instructionType.
         *
         * Process a instruction according the the supplied instructionType.
         *
         * @param[in]   type    instructionType of the to be processed command.
         */
        void process(instructionType type);
        /**
         * @brief       Process and execute the command supplied to this object.
         *
         * Command gets processed and executed.
         */
        void process();
};

#endif // COMMAND_HPP
