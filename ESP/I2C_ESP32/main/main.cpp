#include "LED.hpp"
#include "I2C_ESP.hpp"

extern "C" {
   void app_main();
}

void app_main() {
    auto led = LED();
    led.blinkInfinitely(1000);
	
	gpio_num_t masterSDA = gpio_num_t::GPIO_NUM_18;
	gpio_num_t masterSLC = gpio_num_t::GPIO_NUM_19;
	
	gpio_num_t slaveSDA = gpio_num_t::GPIO_NUM_25;
	gpio_num_t slaveSLC = gpio_num_t::GPIO_NUM_26;
	
	I2cEsp i2cEspMaster(masterSDA, masterSLC, true);
	I2cEsp i2cEspSlave(slaveSDA, slaveSLC);

	
}
