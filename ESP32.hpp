#ifndef ESP32_HPP
#define ESP32_HPP

class ESP32 {
private:
	
	
public:
	ESP32();

	reset();

	set_bank();
	
	read_register();
	write_register();
	
	set_bit();
	erase_bit();
	
	read_buffer();
	write_buffer();
	
};

/// https://github.com/loboris/Lua-RTOS-ESP32-lobo/wiki/ESP32-SPI-pins


#endif // ESP32_HPP