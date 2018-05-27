#include "../src/memory_map.hpp"
#include "catch.hpp"

TEST_CASE("Correct MemoryBlock enum values", "[Static_values]") {
    REQUIRE(MemoryBlock::data_4MB_External_0_L == static_cast<MemoryBlock>(0x3F400000));
    REQUIRE(MemoryBlock::data_4MB_External_0_H == static_cast<MemoryBlock>(0x3F7FFFFF));

    REQUIRE(MemoryBlock::instruction_776KB_Embedded_L == static_cast<MemoryBlock>(0x40000000));
    REQUIRE(MemoryBlock::instruction_776KB_Embedded_H == static_cast<MemoryBlock>(0x400C1FFF));

    REQUIRE(MemoryBlock::data_instruction_8KB_Embedded_L == static_cast<MemoryBlock>(0x50000000));
    REQUIRE(MemoryBlock::data_instruction_8KB_Embedded_H == static_cast<MemoryBlock>(0x50001FFF));
}

TEST_CASE("Correct Register enum values", "[Static_values]") {
    REQUIRE(Register::GPIO_OUT_REG == static_cast<Register>(0x3FF44004));
    REQUIRE(Register::GPIO_OUT_W1TS_REG == static_cast<Register>(0x3FF44008));
    REQUIRE(Register::GPIO_OUT_W1TC_REG == static_cast<Register>(0x3FF4400C));

    REQUIRE(Register::GPIO_FUNC25_OUT_SEL_CFG_REG == static_cast<Register>(0x3FF44594));
    REQUIRE(Register::GPIO_FUNC26_OUT_SEL_CFG_REG == static_cast<Register>(0x3FF44598));
    REQUIRE(Register::GPIO_FUNC27_OUT_SEL_CFG_REG == static_cast<Register>(0x3FF4459C));

    REQUIRE(Register::IO_MUX_MTCK_REG == static_cast<Register>(0x3FF49038));
    REQUIRE(Register::IO_MUX_GPIO16_REG == static_cast<Register>(0x3FF4904C));
    REQUIRE(Register::IO_MUX_SD_CMD_REG == static_cast<Register>(0x3FF4905C));

    REQUIRE(Register::RTCIO_DIG_PAD_HOLD_REG == static_cast<Register>(0x3FF48474));
    REQUIRE(Register::RTCIO_RTC_GPIO_IN_REG == static_cast<Register>(0x3FF48424));
    REQUIRE(Register::RTCIO_RTC_GPIO_PIN0_REG == static_cast<Register>(0x3FF48428));

    REQUIRE(Register::RTCIO_HALL_SENS_REG == static_cast<Register>(0x3FF48478));
    REQUIRE(Register::RTCIO_SENSOR_PADS_REG == static_cast<Register>(0x3FF4847C));
    REQUIRE(Register::RTCIO_ADC_PAD_REG == static_cast<Register>(0x3FF48480));
}
