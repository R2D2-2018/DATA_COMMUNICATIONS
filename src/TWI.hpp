#ifndef TWI_HPP
#define TWI_HPP

/**
 * @file TWI.hpp
 * @brief Abstraction for the TWI (two-wire interface) interface
 * @author Niels de Waal
 * @license see LICENSE
 */

#include "wrap-hwlib.hpp"

#include <array>

namespace TWI {

template <uint32_t SPEED>
class TWI {
  private:
    static constexpr uint32_t masterClock = 84000000; ///< Master clock rate 84MHz

    /**
     * @brief Function to set the TWI clock
     *
     * Function calculates the TWI timings required to reach the specified speed.
     */
    constexpr auto setClock() -> void {
        uint32_t ckdiv  = 0; ///< Clock divider
        uint32_t cLHDiv = 0; ///< Clock low and high divider

        if (SPEED > 400000) {
            return;
        }

        cLHDiv = masterClock / (SPEED * 2) - 4;

        while ((cLHDiv > 0xFF) && (ckdiv < 7)) { ///< cldiv must fit in 8 bits, ckdiv must fit in 3 bits
            ckdiv++;                             ///< Increase clock devider
            cLHDiv /= 2;
        }

        TWI0->TWI_CWGR = TWI_CWGR_CLDIV(cLHDiv) | TWI_CWGR_CHDIV(cLHDiv) | TWI_CWGR_CKDIV(ckdiv);
    }

    /**
     * @brief Write single byte to device.
     *
     * Function writes single byte to a device.
     *
     * @param[in]       data    Byte value
     */
    auto writeByte(const uint8_t data) -> void {
        TWI0->TWI_THR = data;
    }

    /**
     * @brief Read single byte from device.
     *
     * Read a single byte from a device.
     *
     * @return The byte that has been read from the device.
     */
    auto readByte() -> uint8_t {
        return 0;
    }

  public:
    /**
     * @brief TWI constructor.
     *
     * Constructor for the TWI interface.
     */
    TWI() {
        auto config_pin = [](uint32_t pin) {
            PIOA->PIO_ABSR &= (~pin & PIOA->PIO_ABSR);
            PIOA->PIO_PDR  = pin;
            PIOA->PIO_IDR  = pin;
            PIOA->PIO_PUER = pin;
        };

        config_pin(PIO_PA18A_TWCK0);
        config_pin(PIO_PA17A_TWD0);

        if ((PMC->PMC_PCSR0 & (1 << ID_TWI0)) != (1 << ID_TWI0))
            PMC->PMC_PCER0 = 1 << ID_TWI0;

        TWI0->TWI_CR = TWI_CR_SVEN;
        TWI0->TWI_CR = TWI_CR_SWRST;

        TWI0->TWI_CR = TWI_CR_SVDIS;
        TWI0->TWI_CR = TWI_CR_MSDIS;

        TWI0->TWI_CR = TWI_CR_MSEN;

        setClock();
    }

    /**
     * @brief TWI write command
     *
     * Function writes the data containd in the data array to the device specified address.
     *
     * @param[in]       address Address of the device to write to.
     * @param[in]       data    Array containing the data which should be written.
     */
    template <std::size_t LENGTH>
    auto write(const uint8_t address, const std::array<uint8_t, LENGTH> data) -> void {
        TWI0->TWI_MMR  = 0;                       ///< Reset master mode register
        TWI0->TWI_MMR  = 0 << 12 | address << 16; ///< Set write and address
        TWI0->TWI_IADR = 0;                       ///< Clear internal address

        uint32_t status = 0;

        for (const auto &byte : data) {
            status = TWI0->TWI_SR;
            if (status & TWI_SR_NACK) {
                hwlib::cout << "status & NACK" << hwlib::endl;
            }

            if (status & TWI_SR_TXRDY) {
                writeByte(byte);
            }
        }

        while (1) {
            status = TWI0->TWI_SR;
            if (status & TWI_SR_TXRDY) {
                break;
            }
        }

        TWI0->TWI_CR = TWI_CR_STOP;
        while (!(TWI0->TWI_SR & TWI_SR_TXCOMP))
            ;
    }
};

} // namespace TWI

#endif // TWI_HPP
