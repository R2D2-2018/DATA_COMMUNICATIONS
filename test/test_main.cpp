#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/ESP32.hpp"
#include "../src/memory_map.hpp"
#include "wrap-hwlib.hpp"

// VERTICAL_SLICE_1
#include "test_VS1-Dummy_OP_CODES.hpp"
#include "test_VS1-ESP32.hpp"

// VERTICAL_SLICE_2
#include "test_VS2-EnumForRegisters.hpp"
