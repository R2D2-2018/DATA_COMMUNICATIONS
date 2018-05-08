#ifndef ESP32_HPP
#define ESP32_HPP

class ESP32 {
private:
	
	
public:
	ESP32();

	void reset();
	
	int read_register();
	void write_register();
	
	void set_bit();
	void erase_bit();
	
	int read_buffer();
	void write_buffer();
	
};

/// https://github.com/loboris/Lua-RTOS-ESP32-lobo/wiki/ESP32-SPI-pins


#endif // ESP32_HPP