#include "LED.hpp"

LED::LED() {
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
};

void LED::blinkInfinetly(int msDelay) {
    bool isOn = true;
    while (true) {
        if (isOn) {
            *GPIO_w1ts = 1 << 2;
        } else {
            *GPIO_w1tc = 1 << 2;
        }
        isOn = !isOn;
        vTaskDelay(msDelay / portTICK_PERIOD_MS);
    }
};
