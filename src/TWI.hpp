#ifndef TWI_HPP
#define TWI_HPP

#include "wrap-hwlib.hpp"

#include <array>

template <uint32_t SPEED>
class TWI {
  private:
    static constexpr uint32_t masterClock = 84000000;

    constexpr auto setClock() -> void {
        /*
        uint32_t dwCkDiv = 0 ;
        uint32_t dwClDiv = 0;
        uint32_t dwOk = 0 ;

        while ( !dwOk )
        {
            dwClDiv = ((masterClock / (2 * SPEED)) - 4) / (1<<dwCkDiv) ;

            if ( dwClDiv <= 255 )
            {
                dwOk = 1 ;
            }
            else
            {
                dwCkDiv++ ;
            }
        }
        */

        uint32_t ckdiv    = 0;
        uint32_t c_lh_div = 0;

        if (SPEED > 400000) {
            return;
        }

        c_lh_div = masterClock / (SPEED * 2) - 4;

        /* cldiv must fit in 8 bits, ckdiv must fit in 3 bits */
        while ((c_lh_div > 0xFF) && (ckdiv < 7)) {
            /* Increase clock divider */
            ckdiv++;
            /* Divide cldiv value */
            c_lh_div /= 2;
        }

        /* set clock waveform generator register */
        TWI0->TWI_CWGR = TWI_CWGR_CLDIV(c_lh_div) | TWI_CWGR_CHDIV(c_lh_div) | TWI_CWGR_CKDIV(ckdiv);
    }

    auto writeByte(uint8_t data) -> void;
    auto readByte(uint8_t address) -> uint8_t;

    void write_byte(uint8_t byte) {
        TWI0->TWI_THR = byte;
        //hwlib::wait_ms(1);
    }

  public:
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

    void write(uint_fast8_t a, const uint8_t data[], size_t n) {
        TWI0->TWI_MMR  = 0;                 /**< Reset master mode register */
        TWI0->TWI_MMR  = 0 << 12 | a << 16; /**< Set write and address */
        TWI0->TWI_IADR = 0;                 /**< Clear internal address */

        uint32_t status = 0;

        for (size_t i = 0; i < n; ++i) {
            status = TWI0->TWI_SR;
            if (status & TWI_SR_NACK)
                hwlib::cout << "status & NACK" << hwlib::endl;

            if (status & TWI_SR_TXRDY) {
                write_byte(*(data + i));
            }
        }

        while (1) {
            status = TWI0->TWI_SR;
            if (status & TWI_SR_NACK) {
                return;
            }
            if (status & TWI_SR_TXRDY) {
                break;
            }
        }

        TWI0->TWI_CR = TWI_CR_STOP;
        while (!(TWI0->TWI_SR & TWI_SR_TXCOMP))
            ;
    }
};

#endif // TWI_HPP
