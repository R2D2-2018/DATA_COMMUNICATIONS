#ifndef I2C_HPP
#define I2C_HPP

/**
 * @file        I2C.hpp
 * @brief       Abstraction class for I2C
 * @author      Niels de Waal
 * @license     See LICESNSE
 */

#include "wrap-hwlib.hpp"

#include <array>

namespace i2c {

template <uint8_t devAddress>
class i2c {
  private:
    static constexpr uint8_t deviceAddress = devAddress; ///< Address of the I2C device
  public:
    /**
     * @brief   I2C constructor
     *
     * Constructor for the I2C class.
     */
    i2c() {
    }

    /**
     * @brief Function for reading a byte.
     *
     * Function to read a byte using the I2C bus.
     *
     * @param[in]       address The address from which to read a byte
     * @return  The resulting byte.
     */
    auto read(const uint8_t address) -> uint8_t {
        return address;
    }

    /**
     * @brief Function to read multiple bytes
     *
     * Function to read multiple bytes from a device attached to the I2C bus.
     *
     * @param[in]       address The starting address for reading.
     * @return  An array containing the resulting bytes.
     */
    template <std::size_t LENGTH>
    auto read(const uint8_t address) -> std::array<uint8_t, LENGTH> {
        std::array<uint8_t, LENGTH> retArray = {0};
        return retArray;
    }

    /**
     * @brief Function to write multiple bytes to the device
     *
     * Function can write multiple bytes to the device.
     *
     * @param[in]       address The starting address from which to start writing.
     * @param[in]       buffer  A array containing the bytes which will be written.
     */
    template <std::size_t LENGTH>
    auto write(const uint8_t address, const std::array<uint8_t, LENGTH> &buffer) -> void {
        return;
    }

    /**
     * @brief Get function for the configured device address
     *
     * Getter function to return the device address that has been configured.
     *
     * @return  Device address
     */
    auto getDeviceAddress() -> uint8_t {
        return deviceAddress;
    }
};

} // namespace i2c

#endif // I2C_HPP
