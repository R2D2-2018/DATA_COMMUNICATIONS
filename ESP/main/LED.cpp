#include "LED.hpp"

LED::LED(){
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
};

void LED::blinkInfinitly(int msDelay) {
    bool direction = true;
    while (true) {
        if (direction) {
            *GPIO_w1ts = 1 << 2;
        } else {
            *GPIO_w1tc = 1 << 2;
        }
        direction = !direction;
        vTaskDelay(msDelay / portTICK_PERIOD_MS);
    }
};
