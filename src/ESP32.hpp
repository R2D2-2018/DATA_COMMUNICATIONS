/**
 * @file
 * @brief     ESP32 class - containing (SPI) commands.
 * @author    Roxanne van der Pol
 * @license   MIT
 */

#ifndef ESP32_HPP
#define ESP32_HPP

class ESP32 {
private:
	
public:
	ESP32();

	/**
	 * @brief Resets the ESP32 chip
	 * 
	 * Resets the ESP32 chip by sending it a Reset command.
	 * 
	 */
	void reset();
	
	/**
	 * @brief Reads a register from the ESP32 chip
	 * 
	 * Reads a register from the ESP32 chip by sending it a read_register command.
	 * 
	 * @param[in] address The address to be read
	 * @return data read from the specified register
	 */
	int readRegister(int address);
	/**
	 * @brief Writes to a register from the ESP32 chip
	 * 
	 * Writes to a register from the ESP32 chip by sending it a write_register command.
	 * 
	 * @param[in] address The address to write to
	 * @param[in] data The data to be written to the specified register
	 */
	void writeRegister(int address, int data);
	
	/**
	 * @brief Sets a bit in a register from the ESP32 chip
	 * 
	 * Sets a bit to 1 in a register from the ESP32 chip by sending it the set_bit command
	 * 
	 */
	void setBit();
	/**
	 * @brief Erases a bit in a register from the ESP32 chip
	 * 
	 * Sets a bit to 0 in a register from the ESP32 chip by sending it the erase_bit command.
	 * 
	 */
	void eraseBit();
	
	/**
	 * @brief Reads received data from the receive buffer of the ESP32 chip
	 * 
	 * Reads received data from the receive buffer of the ESP32 chip by sending it the read_buffer command.
	 * 
	 * @return data The data read from the receive buffer
	 */
	int readBuffer();
	/**
	 * @brief Writes data to the transmit buffer of the ESP32 chip
	 * 
	 * Writes data to be sent to the transmit buffer of the ESP32 chip by sending it a write_buffer command.
	 * 
	 * @param[in] data The data to be written to the transmit buffer of the ESP32 for sending
	 */
	void writeBuffer(int data);
	
};

#endif // ESP32_HPP