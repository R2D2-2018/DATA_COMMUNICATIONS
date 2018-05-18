#include "catch.hpp"
#include "../src/memory_map.hpp"

TEST_CASE( "Correct MemoryBlock enum values", "[Static_values]" ){
	REQUIRE(data_4MB_External_0_L == 0x3F400000);
	REQUIRE(data_4MB_External_0_H == 0x3F7FFFFF);
	
	REQUIRE(instruction_776KB_Embedded_L == 0x40000000);
	REQUIRE(instruction_776KB_Embedded_H == 0x400C1FFF);
	
	REQUIRE(data_instruction_8KB_Embedded_L == 0x50000000);
	REQUIRE(data_instruction_8KB_Embedded_H == 0x50001FFF);
}

TEST_CASE( "Correct Register enum values", "[Static_values]" ){
	REQUIRE(GPIO_OUT_REG == 0x3FF44004);
	REQUIRE(GPIO_OUT_W1TS_REG == 0x3FF44008);
	REQUIRE(GPIO_OUT_W1TC_REG == 0x3FF4400C);
	
	REQUIRE(GPIO_FUNC25_OUT_SEL_CFG_REG	== 0x3FF44594);
	REQUIRE(GPIO_FUNC26_OUT_SEL_CFG_REG	== 0x3FF44598);
	REQUIRE(GPIO_FUNC27_OUT_SEL_CFG_REG	== 0x3FF4459C);
	
	REQUIRE(IO_MUX_MTCK_REG	== 0x3FF49038);
	REQUIRE(IO_MUX_GPIO16_REG == 0x3FF4904C);
	REQUIRE(IO_MUX_SD_CMD_REG == 0x3FF4905C);

	REQUIRE(RTCIO_DIG_PAD_HOLD_REG == 0x3FF48474);
	REQUIRE(RTCIO_RTC_GPIO_IN_REG == 0x3FF48424);
	REQUIRE(RTCIO_RTC_GPIO_PIN0_REG	== 0x3FF48428);

	REQUIRE(RTCIO_HALL_SENS_REG	== 0x3FF48478);
	REQUIRE(RTCIO_SENSOR_PADS_REG == 0x3FF4847C);
	REQUIRE(RTCIO_ADC_PAD_REG == 0x3FF48480);
}

