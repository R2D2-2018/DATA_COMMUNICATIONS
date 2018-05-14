#ifndef MEMORY_MAP_HPP
#define MEMORY_MAP_HPP

/**
 * @file        memory_map.hpp
 * @brief       This header will contain memory addresses, used for controlling the ESP32
 * @author      Niels de Waal
 * @license     MIT
 */

enum BaseAddresses: uint16_t {
    GPIO_FUNC_OUT_SEL_CFG_REG = 0x530
}

#endif // MEMORY_MAP_HPP
