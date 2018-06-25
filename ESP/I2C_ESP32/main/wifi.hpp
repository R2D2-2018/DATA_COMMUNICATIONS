/* ESPNOW Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifndef WIFI_HPP
#define WIFI_HPP

#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_system.h"
#include "esp_wifi.h"
//#include "espnow_example.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
// #include "nvs_flash.h"
#include "rom/crc.h"
#include "rom/ets_sys.h"
#include "tcpip_adapter.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ESPNOW can work in both station and softap mode. It is configured in menuconfig. */
#if CONFIG_STATION_MODE
#define WIFI_MODE WIFI_MODE_STA
#define WIFI_IF ESP_IF_WIFI_STA
#else
#define WIFI_MODE WIFI_MODE_AP
#define WIFI_IF ESP_IF_WIFI_AP
#endif

#define QUEUE_SIZE 6

#define IS_BROADCAST_ADDR(addr) (memcmp(addr, broadcast_mac, ESP_NOW_ETH_ALEN) == 0)

typedef enum {
    SEND_CB,
    RECV_CB,
} event_id_t;

typedef struct {
    uint8_t mac_addr[ESP_NOW_ETH_ALEN];
    esp_now_send_status_t status;
} event_send_cb_t;

typedef struct {
    uint8_t mac_addr[ESP_NOW_ETH_ALEN];
    uint8_t *data;
    int data_len;
} event_recv_cb_t;

typedef union {
    event_send_cb_t send_cb;
    event_recv_cb_t recv_cb;
} event_info_t;

/* When ESPNOW sending or receiving callback function is called, post event to ESPNOW task. */
typedef struct {
    event_id_t id;
    event_info_t info;
} event_t;

enum {
    DATA_BROADCAST,
    DATA_UNICAST,
    DATA_MAX,
};

/* User defined field of ESPNOW data in this example. */
typedef struct {
    uint8_t type;       // Broadcast or unicast ESPNOW data.
    uint8_t state;      // Indicate that if has received broadcast ESPNOW data or not.
    uint16_t seq_num;   // Sequence number of ESPNOW data.
    uint16_t crc;       // CRC16 value of ESPNOW data.
    uint32_t magic;     // Magic number which is used to determine which device to send unicast ESPNOW data.
    uint8_t payload[0]; // Real payload of ESPNOW data.
} __attribute__((packed)) data_t;

/* Parameters of sending ESPNOW data. */
typedef struct {
    bool unicast;                       // Send unicast ESPNOW data.
    bool broadcast;                     // Send broadcast ESPNOW data.
    uint8_t state;                      // Indicate that if has received broadcast ESPNOW data or not.
    uint32_t magic;                     // Magic number which is used to determine which device to send unicast ESPNOW data.
    uint16_t count;                     // Total count of unicast ESPNOW data to be sent.
    uint16_t delay;                     // Delay between sending two ESPNOW data, unit: ms.
    int len;                            // Length of ESPNOW data to be sent, unit: byte.
    uint8_t *buffer;                    // Buffer pointing to ESPNOW data.
    uint8_t dest_mac[ESP_NOW_ETH_ALEN]; // MAC address of destination device.
} send_param_t;

class Wifi {

  public:
    Wifi();

    /**
     * @brief switches events
     * 
     * @description This function switches between events like wifi started.
     *
     * @parama
     * event : system_event_t * // the even you want the change to.
     * 
     * @return 
     * ESP_OK : esp_err_t
     */
    static esp_err_t event_handler(void *ctx, system_event_t *event);

    /**
     * @brief Short description of foo
     *
     * description of foo
     * [BLANK]
     * @param[in]     a    What is the input for the function
     * @return What will the function return
     */
    static void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status);

    static void recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);

    static int data_parse(uint8_t *data, uint16_t data_len, uint8_t *state, uint16_t *seq, int *magic);

    static void data_prepare(send_param_t *send_param);

    static void task(void *pvParameter);

    static esp_err_t init(void);

    static void deinit(send_param_t *send_param);
};

#endif