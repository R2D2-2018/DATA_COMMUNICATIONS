#ifndef MEMORY_MAP_HPP
#define MEMORY_MAP_HPP

/**
 * @file        memory_map.hpp
 * @brief       This header will contain memory addresses, used for controlling the ESP32
 * @author      Niels de Waal & Roxanne van der Pol
 * @license     MIT
 */

enum BaseAddresses: uint16_t {
    GPIO_FUNC_OUT_SEL_CFG_REG = 0x530
};

enum MemoryBlock: uint64_t {
	// DATA
	data_4MB_External_0_L 		= 0x3F400000,
	data_4MB_External_0_H 		= 0x3F7FFFFF,
	//	
	data_4MB_External_1_L 		= 0x3F800000,
	data_4MB_External_1_H 		= 0x3FBFFFFF,
	//
	data_512KB_Peripheral_0_L 	= 0x3FF00000,
	data_512KB_Peripheral_0_H 	= 0x3FF7FFFF,
	//
	data_512KB_Embedded_0_L 	= 0x3FF80000,
	data_512KB_Embedded_0_H 	= 0x3FFFFFFF,
	
	// INSTRUCTION
	instruction_776KB_Embedded_L	= 0x40000000,
	instruction_776KB_Embedded_H	= 0x400C1FFF,
	//
	instruction_11512KB_External_L	= 0x400C2000,
	instruction_11512KB_External_H	= 0x40BFFFFF,
	
	// DATA_INSTRUCTION
	data_instruction_8KB_Embedded_L = 0x50000000,
	data_instruction_8KB_Embedded_H = 0x50001FFF
};

enum Register: uint64_t {
	GPIO_OUT_REG		= 0x3FF44004,		// R/W
	GPIO_OUT_W1TS_REG	= 0x3FF44008,		// WO
	GPIO_OUT_W1TC_REG	= 0x3FF4400C,		// WO

	GPIO_OUT1_REG		= 0x3FF44010,		// R/W
	GPIO_OUT1_W1TS_REG	= 0x3FF44014,		// WO
	GPIO_OUT1_W1TC_REG	= 0x3FF44018,		// WO

	GPIO_ENABLE_REG			= 0x3FF44020,	// R/W
	GPIO_ENABLE_W1TS_REG	= 0x3FF44024,	// WO
	GPIO_ENABLE_W1TC_REG	= 0x3FF44028,	// WO
		
	GPIO_ENABLE1_REG		= 0x3FF4402C,	// R/W
	GPIO_ENABLE1_W1TS_REG	= 0x3FF44030,	// WO
	GPIO_ENABLE1_W1TC_REG	= 0x3FF44034,	// WO
	
	GPIO_STRAP_REG	= 0x3FF44038,			// RO
		
	GPIO_IN_REG		= 0x3FF4403C,			// RO
	GPIO_IN1_REG	= 0x3FF44040,			// RO
	
	GPIO_STATUS_REG			= 0x3FF44044,	// R/W
	GPIO_STATUS_W1TS_REG	= 0x3FF44048,	// WO
	GPIO_STATUS_W1TC_REG	= 0x3FF4404C,	// WO
		
	GPIO_STATUS1_REG		= 0x3FF44050,	// R/W
	GPIO_STATUS1_W1TS_REG	= 0x3FF44054,	// WO
	GPIO_STATUS1_W1TC_REG	= 0x3FF44058,	// WO

	GPIO_ACPU_INT_REG		= 0x3FF44060,	// RO
	GPIO_ACPU_NMI_INT_REG	= 0x3FF44064,	// RO

	GPIO_PCPU_INT_REG		= 0x3FF44068,	// RO
	GPIO_PCPU_NMI_INT_REG	= 0x3FF4406C,	// RO

	GPIO_ACPU_INT1_REG		= 0x3FF44074,	// RO
	GPIO_ACPU_NMI_INT1_REG	= 0x3FF44078,	// RO
		
	GPIO_PCPU_INT1_REG		= 0x3FF4407C,	// RO
	GPIO_PCPU_NMI_INT1_REG	= 0x3FF44080,	// RO
		
	GPIO_PIN0_REG	= 0x3FF44088,	// R/W
	GPIO_PIN1_REG	= 0x3FF4408C,	// R/W
	GPIO_PIN2_REG	= 0x3FF44090,	// R/W
	GPIO_PIN3_REG	= 0x3FF44094,	// R/W
	GPIO_PIN4_REG	= 0x3FF44098,	// R/W
	GPIO_PIN5_REG	= 0x3FF4409C,	// R/W
	GPIO_PIN6_REG	= 0x3FF440A0,	// R/W
	GPIO_PIN7_REG	= 0x3FF440A4,	// R/W
	GPIO_PIN8_REG	= 0x3FF440A8,	// R/W
	GPIO_PIN9_REG	= 0x3FF440AC,	// R/W
	//
	GPIO_PIN10_REG	= 0x3FF440B0,	// R/W
	GPIO_PIN11_REG	= 0x3FF440B4,	// R/W
	GPIO_PIN12_REG	= 0x3FF440B8,	// R/W
	GPIO_PIN13_REG	= 0x3FF440BC,	// R/W
	GPIO_PIN14_REG	= 0x3FF440C0,	// R/W
	GPIO_PIN15_REG	= 0x3FF440C4,	// R/W
	GPIO_PIN16_REG	= 0x3FF440C8,	// R/W
	GPIO_PIN17_REG	= 0x3FF440CC,	// R/W
	GPIO_PIN18_REG	= 0x3FF440D0,	// R/W
	GPIO_PIN19_REG	= 0x3FF440D4,	// R/W
	//
	GPIO_PIN20_REG	= 0x3FF440D8,	// R/W
	GPIO_PIN21_REG	= 0x3FF440DC,	// R/W
	GPIO_PIN22_REG	= 0x3FF440E0,	// R/W
	GPIO_PIN23_REG	= 0x3FF440E4,	// R/W
	GPIO_PIN24_REG	= 0x3FF440E8,	// R/W
	GPIO_PIN25_REG	= 0x3FF440EC,	// R/W
	GPIO_PIN26_REG	= 0x3FF440F0,	// R/W
	GPIO_PIN27_REG	= 0x3FF440F4,	// R/W
	GPIO_PIN28_REG	= 0x3FF440F8,	// R/W
	GPIO_PIN29_REG	= 0x3FF440FC,	// R/W
	//
	GPIO_PIN30_REG	= 0x3FF44100,	// R/W
	GPIO_PIN31_REG	= 0x3FF44104,	// R/W
	GPIO_PIN32_REG	= 0x3FF44108,	// R/W
	GPIO_PIN33_REG	= 0x3FF4410,	// R/W
	GPIO_PIN34_REG	= 0x3FF44110,	// R/W
	GPIO_PIN35_REG	= 0x3FF44114,	// R/W
	GPIO_PIN36_REG	= 0x3FF44118,	// R/W
	GPIO_PIN37_REG	= 0x3FF4411,	// R/W
	GPIO_PIN38_REG	= 0x3FF44120,	// R/W
	GPIO_PIN39_REG	= 0x3FF44124,	// R/W

	GPIO_FUNC0_IN_SEL_CFG_REG	= 0x3FF44130,	// R/W
	GPIO_FUNC1_IN_SEL_CFG_REG	= 0x3FF44134,	// R/W
	// ~ //
	GPIO_FUNC254_IN_SEL_CFG_REG	= 0x3FF44528,	// R/W
	GPIO_FUNC255_IN_SEL_CFG_REG	= 0x3FF4452C,	// R/W
		
	GPIO_FUNC0_OUT_SEL_CFG_REG	= 0x3FF44530,	// R/W
	GPIO_FUNC1_OUT_SEL_CFG_REG	= 0x3FF44534,	// R/W
	GPIO_FUNC2_OUT_SEL_CFG_REG	= 0x3FF44538,	// R/W
	GPIO_FUNC3_OUT_SEL_CFG_REG	= 0x3FF4453C,	// R/W
	GPIO_FUNC4_OUT_SEL_CFG_REG	= 0x3FF44540,	// R/W
	GPIO_FUNC5_OUT_SEL_CFG_REG	= 0x3FF44544,	// R/W
	GPIO_FUNC6_OUT_SEL_CFG_REG	= 0x3FF44548,	// R/W
	GPIO_FUNC7_OUT_SEL_CFG_REG	= 0x3FF4454C,	// R/W
	GPIO_FUNC8_OUT_SEL_CFG_REG	= 0x3FF44550,	// R/W
	GPIO_FUNC9_OUT_SEL_CFG_REG	= 0x3FF44554,	// R/W
	//
	GPIO_FUNC10_OUT_SEL_CFG_REG	= 0x3FF44558,	// R/W
	GPIO_FUNC11_OUT_SEL_CFG_REG	= 0x3FF4455C,	// R/W
	GPIO_FUNC12_OUT_SEL_CFG_REG	= 0x3FF44560,	// R/W
	GPIO_FUNC13_OUT_SEL_CFG_REG	= 0x3FF44564,	// R/W
	GPIO_FUNC14_OUT_SEL_CFG_REG	= 0x3FF44568,	// R/W
	GPIO_FUNC15_OUT_SEL_CFG_REG	= 0x3FF4456C,	// R/W
	GPIO_FUNC16_OUT_SEL_CFG_REG	= 0x3FF44570,	// R/W
	GPIO_FUNC17_OUT_SEL_CFG_REG	= 0x3FF44574,	// R/W
	GPIO_FUNC18_OUT_SEL_CFG_REG	= 0x3FF44578,	// R/W
	GPIO_FUNC19_OUT_SEL_CFG_REG	= 0x3FF4457C,	// R/W
	//
	GPIO_FUNC20_OUT_SEL_CFG_REG	= 0x3FF44580,	// R/W
	GPIO_FUNC21_OUT_SEL_CFG_REG	= 0x3FF44584,	// R/W
	GPIO_FUNC22_OUT_SEL_CFG_REG	= 0x3FF44588,	// R/W
	GPIO_FUNC23_OUT_SEL_CFG_REG	= 0x3FF4458C,	// R/W
	GPIO_FUNC24_OUT_SEL_CFG_REG	= 0x3FF44590,	// R/W
	GPIO_FUNC25_OUT_SEL_CFG_REG	= 0x3FF44594,	// R/W
	GPIO_FUNC26_OUT_SEL_CFG_REG	= 0x3FF44598,	// R/W
	GPIO_FUNC27_OUT_SEL_CFG_REG	= 0x3FF4459C,	// R/W
	GPIO_FUNC28_OUT_SEL_CFG_REG	= 0x3FF445A0,	// R/W
	GPIO_FUNC29_OUT_SEL_CFG_REG	= 0x3FF445A4,	// R/W
	//
	GPIO_FUNC30_OUT_SEL_CFG_REG	= 0x3FF445A8,	// R/W
	GPIO_FUNC31_OUT_SEL_CFG_REG	= 0x3FF445AC,	// R/W
	GPIO_FUNC32_OUT_SEL_CFG_REG	= 0x3FF445B0,	// R/W
	GPIO_FUNC33_OUT_SEL_CFG_REG	= 0x3FF445B4,	// R/W
	GPIO_FUNC34_OUT_SEL_CFG_REG	= 0x3FF445B8,	// R/W
	GPIO_FUNC35_OUT_SEL_CFG_REG	= 0x3FF445BC,	// R/W
	GPIO_FUNC36_OUT_SEL_CFG_REG	= 0x3FF445C0,	// R/W
	GPIO_FUNC37_OUT_SEL_CFG_REG	= 0x3FF445C4,	// R/W
	GPIO_FUNC38_OUT_SEL_CFG_REG	= 0x3FF445C8,	// R/W
	GPIO_FUNC39_OUT_SEL_CFG_REG	= 0x3FF445CC,	// R/W
	
	IO_MUX_PIN_CTRL		= 0x3FF49000,	// R/W

	IO_MUX_GPIO36_REG	= 0x3FF49004,	// R/W
	IO_MUX_GPIO37_REG	= 0x3FF49008,	// R/W
	IO_MUX_GPIO38_REG	= 0x3FF4900C,	// R/W
	IO_MUX_GPIO39_REG	= 0x3FF49010,	// R/W
	IO_MUX_GPIO34_REG	= 0x3FF49014,	// R/W
	IO_MUX_GPIO35_REG	= 0x3FF49018,	// R/W
	IO_MUX_GPIO32_REG	= 0x3FF4901C,	// R/W
	IO_MUX_GPIO33_REG	= 0x3FF49020,	// R/W
	IO_MUX_GPIO25_REG	= 0x3FF49024,	// R/W
	IO_MUX_GPIO26_REG	= 0x3FF49029,	// R/W
	IO_MUX_GPIO27_REG	= 0x3FF4902C,	// R/W
	
	IO_MUX_MTMS_REG		= 0x3FF49030,	// R/W
	IO_MUX_MTDI_REG		= 0x3FF49034,	// R/W
	IO_MUX_MTCK_REG		= 0x3FF49038,	// R/W
	IO_MUX_MTDO_REG		= 0x3FF4903C,	// R/W

	IO_MUX_GPIO2_REG	= 0x3FF49040,	// R/W
	IO_MUX_GPIO0_REG	= 0x3FF49044,	// R/W
	IO_MUX_GPIO4_REG	= 0x3FF49048,	// R/W
	IO_MUX_GPIO16_REG	= 0x3FF4904C,	// R/W
	IO_MUX_GPIO17_REG	= 0x3FF49050,	// R/W
		
	IO_MUX_SD_DATA2_REG	= 0x3FF49054,	// R/W
	IO_MUX_SD_DATA3_REG	= 0x3FF49058,	// R/W
		
	IO_MUX_SD_CMD_REG	= 0x3FF4905C,	// R/W
	IO_MUX_SD_CLK_REG	= 0x3FF49060,	// R/W
	
	IO_MUX_SD_DATA0_REG	= 0x3FF49064,	// R/W
	IO_MUX_SD_DATA1_REG	= 0x3FF49068,	// R/W
		
	IO_MUX_GPIO5_REG	= 0x3FF4906C,	// R/W
	IO_MUX_GPIO18_REG	= 0x3FF49070,	// R/W
	IO_MUX_GPIO19_REG	= 0x3FF49074,	// R/W
	IO_MUX_GPIO20_REG	= 0x3FF49078,	// R/W
	IO_MUX_GPIO21_REG	= 0x3FF4907C,	// R/W
	IO_MUX_GPIO22_REG	= 0x3FF49080,	// R/W
		
	IO_MUX_U0RXD_REG	= 0x3FF49084,	// R/W
	IO_MUX_U0TXD_REG	= 0x3FF49088,	// R/W
	
	IO_MUX_GPIO23_REG	= 0x3FF4908C,	// R/W
	IO_MUX_GPIO24_REG	= 0x3FF49090,	// R/W
		
	// GPIO CONFIGURATION / DATA REGISTERS
		
	RTCIO_RTC_GPIO_OUT_REG			= 0x3FF48400,	// R/W
	RTCIO_RTC_GPIO_OUT_W1TS_REG		= 0x3FF48404,	// WO
	RTCIO_RTC_GPIO_OUT_W1TC_REG		= 0x3FF48408,	// WO
	
	RTCIO_RTC_GPIO_ENABLE_REG		= 0x3FF4840C,	// R/W
	RTCIO_RTC_GPIO_ENABLE_W1TS_REG	= 0x3FF48410,	// WO
	RTCIO_RTC_GPIO_ENABLE_W1TC_REG	= 0x3FF48414,	// WO
	
	RTCIO_RTC_GPIO_STATUS_REG		= 0x3FF48418,	// WO
	RTCIO_RTC_GPIO_STATUS_W1TS_REG	= 0x3FF4841C,	// WO
	RTCIO_RTC_GPIO_STATUS_W1TC_REG	= 0x3FF48420,	// WO
		
	RTCIO_RTC_GPIO_IN_REG		= 0x3FF48424,	// RO

	RTCIO_RTC_GPIO_PIN0_REG		= 0x3FF48428,	// R/W
	RTCIO_RTC_GPIO_PIN1_REG		= 0x3FF4842C,	// R/W
	RTCIO_RTC_GPIO_PIN2_REG		= 0x3FF48430,	// R/W
	RTCIO_RTC_GPIO_PIN3_REG		= 0x3FF48434,	// R/W
	RTCIO_RTC_GPIO_PIN4_REG		= 0x3FF48438,	// R/W
	RTCIO_RTC_GPIO_PIN5_REG		= 0x3FF4843C,	// R/W
	RTCIO_RTC_GPIO_PIN6_REG		= 0x3FF48440,	// R/W
	RTCIO_RTC_GPIO_PIN7_REG		= 0x3FF48444,	// R/W
	RTCIO_RTC_GPIO_PIN8_REG		= 0x3FF48448,	// R/W
	RTCIO_RTC_GPIO_PIN9_REG		= 0x3FF4844C,	// R/W
	//
	RTCIO_RTC_GPIO_PIN10_REG	= 0x3FF48450,	// R/W
	RTCIO_RTC_GPIO_PIN11_REG	= 0x3FF48454,	// R/W
	RTCIO_RTC_GPIO_PIN12_REG	= 0x3FF48458,	// R/W
	RTCIO_RTC_GPIO_PIN13_REG	= 0x3FF48450,	// R/W
	RTCIO_RTC_GPIO_PIN14_REG	= 0x3FF48460,	// R/W
	RTCIO_RTC_GPIO_PIN15_REG	= 0x3FF48464,	// R/W
	RTCIO_RTC_GPIO_PIN16_REG	= 0x3FF48468,	// R/W
	RTCIO_RTC_GPIO_PIN17_REG	= 0x3FF4846C,	// R/W
	
	RTCIO_DIG_PAD_HOLD_REG		= 0x3FF48474,	// R/W
		
	// GPIO RTC FUNCTION CONFIGURATION REGISTERS
	
	RTCIO_HALL_SENS_REG			= 0x3FF48478,	// R/W
	RTCIO_SENSOR_PADS_REG		= 0x3FF4847C,	// R/W
	RTCIO_ADC_PAD_REG			= 0x3FF48480,	// R/W
	
	RTCIO_PAD_DAC1_REG		= 0x3FF48484,	// R/W
	RTCIO_PAD_DAC2_REG		= 0x3FF48488,	// R/W
	
	RTCIO_XTAL_32K_PAD_REG	= 0x3FF4848C,	// R/W
	
	RTCIO_TOUCH_CFG_REG		= 0x3FF48490,	// R/W
	RTCIO_TOUCH_PAD0_REG	= 0x3FF48494,	// R/W
	RTCIO_TOUCH_PAD1_REG	= 0x3FF48498,	// R/W
	RTCIO_TOUCH_PAD2_REG	= 0x3FF4849C,	// R/W
	RTCIO_TOUCH_PAD3_REG	= 0x3FF484A0,	// R/W
	RTCIO_TOUCH_PAD4_REG	= 0x3FF484A4,	// R/W
	RTCIO_TOUCH_PAD5_REG	= 0x3FF484A8,	// R/W
	RTCIO_TOUCH_PAD6_REG	= 0x3FF484AC,	// R/W
	RTCIO_TOUCH_PAD7_REG	= 0x3FF484B0,	// R/W
	RTCIO_TOUCH_PAD8_REG	= 0x3FF484B4,	// R/W
	RTCIO_TOUCH_PAD9_REG	= 0x3FF484B8,	// R/W

	RTCIO_EXT_WAKEUP0_REG	= 0x3FF484BC,	// R/W
	RTCIO_XTL_EXT_CTR_REG	= 0x3FF484C0,	// R/W
	RTCIO_SAR_I2C_IO_REG	= 0x3FF484C4	// R/W
		
};

#endif // MEMORY_MAP_HPP
