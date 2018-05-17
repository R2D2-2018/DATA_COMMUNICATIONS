#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

// VERTICAL_SLICE_1
#include "test_VS1-ESP32.cpp"
#include "test_VS1-Dummy_OP_CODES.cpp"

// VERTICAL_SLICE_2
#include "test_VS2-EnumForRegisters.cpp"