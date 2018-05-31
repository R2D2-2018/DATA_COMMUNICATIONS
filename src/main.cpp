#include "wrap-hwlib.hpp"
#include "ESP32.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
	
    hwlib::wait_ms(2500);
	
    return 0;
}
