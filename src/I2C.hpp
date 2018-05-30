#ifndef I2C_HPP
#define I2C_HPP

#include <array>

#include "wrap-hwlib.hpp"

namespace I2C {

class I2C {
  private:
  public:
    I2C();

    auto read(const uint8_t address) -> uint8_t;

    template <std::size_t length>
    auto read(const uint8_t address) -> std::array<uint8_t, length>;

    template <std::size_t length>
    auto read(const uint8_t address) -> std::array<uint8_t, length> &;

    template <std::size_t length>
    auto write(const uint8_t address, std::array<uint8_t, length> buffer) -> void;

    template <std::size_t length>
    auto write(const uint8_t address, std::array<uint8_t, length> &buffer) -> void;
};

} // namespace I2C

#endif // I2C_HPP
