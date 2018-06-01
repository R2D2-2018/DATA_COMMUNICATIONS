#ifndef I2C_HPP
#define I2C_HPP

#include <array>

#include "wrap-hwlib.hpp"

namespace I2C {

class I2C {
  private:
  public:
    I2C();

    auto read(const uint8_t address) -> uint8_t {
        return address;
    }

    template <std::size_t LENGTH>
    auto read(const uint8_t address) -> std::array<uint8_t, LENGTH> {
        std::array<uint8_t, LENGTH> retArray = {0};
        return retArray;
    }

    /*
    template <std::size_t length>
    auto write(const uint8_t address, std::array<uint8_t, length> buffer) -> void {
    */

    template <std::size_t length>
    auto write(uint8_t address, std::array<uint8_t, length> &buffer) -> void {
        return;
    }
};

} // namespace I2C

#endif // I2C_HPP
