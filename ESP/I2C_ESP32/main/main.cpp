#include "wifi.hpp"
#include <stdlib.h>

extern "C" {
void app_main();
}

void app_main() {

    Wifi wifi;

    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // wifi.example_wifi_init();
    wifi.example_espnow_init();
}
