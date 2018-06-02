#include "ESP32.hpp"
#include "memory_map.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
	
    hwlib::wait_ms(2500);
	
    return 0;
}
