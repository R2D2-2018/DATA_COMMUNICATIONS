#include "esp32.hpp"
#include "i2c.hpp"
#include "memory_map.hpp"
#include "twi.hpp"
#include "wrap-hwlib.hpp"

#include <array>

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    return 0;
}
