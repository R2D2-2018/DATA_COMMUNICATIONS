#ifndef COMMAND_HPP
#define COMMAND_HPP

/**
 * @file        command.hpp
 * @brief       Class for sending commands to the ESP32
 * @author      Niels de Waal
 * @license     MIT
 */

#include "SPI.hpp"
#include "wrap-hwlib.hpp"

#include <array>
#include <functional>
#include <utility>

class Command {
    private:
        uint8_t type; ///< Type of the command, either read or write.
        uint8_t location; ///< Location of the command.
        std::array<uint8_t, 2> data = {0x00, 0x00};
    public:
        /**
         * @brief       Constructor for command object
         * 
         * Constructor for the command object.
         * Command objects are an abstraction for the commands that can be send 
         * to the ESP32.
         * 
         * @param[in]   type            Type of the command to be send.
         * @param[in]   location        Location of the read or write.
         * @return What will the function return
         */
        Command(uint8_t type, uint8_t location);

        /**
         * @brief       Returns the command data
         *
         * Function returns the type and data of a command object.
         *
         * @return pair containing the type and location of a command
         */
        std::pair<uint8_t, uint8_t> getCommandData();
        /**
         * @brief       Sets the data of a command.
         *
         * Function to set the data of a command.
         * Used for write command where the data has an effect.
         *
         * @param[in]   sendData        array containing the data that needs to be send.
         */
        void setData(std::array<uint8_t, 2> sendData);
        /**
         * @brief       Function to change the type and location of a command.
         *
         * Function to change the data and location of a command.
         *
         * @param[in]   type            New type of the command.
         * @param[in]   location        New location of the command.
         */
        void changeCommand(uint8_t type, uint8_t location);
        /**
         * @brief       Function to send the stored command.
         *
         * Function loads the data stored in the object and sends it to the ESP32.
         */
        void sendCommand();
};

#endif // COMMAND_HPP
