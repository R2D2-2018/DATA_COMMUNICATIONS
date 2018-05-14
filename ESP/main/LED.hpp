#ifndef LED_HPP
#define LED_HPP

/**
 * @file        LED.hpp
 * @brief       Simple class for controlling the onboard LED.
 * @author      Niels de Waal
 * @license     MIT
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

class LED {
    private:
        uint32_t* GPIO_w1ts = (uint32_t*)0x3ff44008; ///< Output set register
        uint32_t* GPIO_w1tc = (uint32_t*)0x3ff4400c; ///< Output clear register

    public:
        /**
         * @brief Contructor for the LED class
         * 
         * Contructor for the LED class.
         */
        LED();

        /**
         * @brief blinks the led infinitly
         * 
         * Blinks the LED infinitly.
         * This will put the ESP into an infinite loop.
         * 
         * @param[in]     msDelay    Amount of ms delay between state change
         */
        void blinkInfinitly(int msDelay);
        /**
         * @brief blinks the led for a set amount of times
         * 
         * This function wil blink the LED a set amount of times.
         * The delay is also controllable.
         * 
         * @param[in]   amount     The amount of times the LED will blink
         * @param[in]   msDelay    Amount of ms delay between state change
         */
        void blinkAmount(int amount, int msDelay);

};

#endif // LED_HPP
