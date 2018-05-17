#include "wrap-hwlib.hpp"
#include "ESP32.hpp"
#include "memory_map.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    return 0;
}
