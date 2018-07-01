/**
 * @file
 * @brief     esp32 class - containing (SPI) commands.
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#ifndef esp32_HPP
#define esp32_HPP

//#include "command.hpp"

#include <array>

class esp32 {
  private:
  public:
    esp32();

    /**
     * @brief Resets the esp32 chip
     *
     * Resets the esp32 chip by sending it a Reset command.
     *
     */
    void reset();

    /**
     * @brief Reads a register from the esp32 chip
     *
     * Reads a register from the esp32 chip by sending it a read_register command.
     *
     * @param[in] address The address to be read
     * @return data read from the specified register
     */
    int readRegister(int address);
    /**
     * @brief Writes to a register from the esp32 chip
     *
     * Writes to a register from the esp32 chip by sending it a write_register command.
     *
     * @param[in] address The address to write to
     * @param[in] data The data to be written to the specified register
     */
    void writeRegister(int address, std::array<uint8_t, 2> data);

    /**
     * @brief Sets a bit in a register from the esp32 chip
     *
     * Sets a bit to 1 in a register from the esp32 chip by sending it the set_bit command
     *
     */
    void setBit();
    /**
     * @brief Erases a bit in a register from the esp32 chip
     *
     * Sets a bit to 0 in a register from the esp32 chip by sending it the erase_bit command.
     *
     */
    void eraseBit();

    /**
     * @brief Reads received data from the receive buffer of the esp32 chip
     *
     * Reads received data from the receive buffer of the esp32 chip by sending it the read_buffer command.
     *
     * @return data The data read from the receive buffer
     */
    int readBuffer();
    /**
     * @brief Writes data to the transmit buffer of the esp32 chip
     *
     * Writes data to be sent to the transmit buffer of the esp32 chip by sending it a write_buffer command.
     *
     * @param[in] data The data to be written to the transmit buffer of the esp32 for sending
     */
    void writeBuffer(int data);
};

#endif // esp32_HPP
