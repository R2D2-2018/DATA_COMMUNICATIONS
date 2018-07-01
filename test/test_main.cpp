#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/esp32.hpp"
#include "../src/memory_map.hpp"

// VERTICAL_SLICE_1
#include "test_VS1-Dummy_OP_CODES.hpp"

// VERTICAL_SLICE_2
#include "test_VS2-EnumForRegisters.hpp"

// VERTICAL_SLICE_3
#include "test_VS3_I2C_Base.hpp"
