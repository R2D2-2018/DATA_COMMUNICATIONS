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
    uint32_t deviceNum;     // Magic number which is used to determine which device to send unicast ESPNOW data.
    uint8_t payload[0]; // Real payload of ESPNOW data.
} __attribute__((packed)) data_t;

/* Parameters of sending ESPNOW data. */
typedef struct {
    bool unicast;                       // Send unicast ESPNOW data.
    bool broadcast;                     // Send broadcast ESPNOW data.
    uint8_t state;                      // Indicate that if has received broadcast ESPNOW data or not.
    uint32_t deviceNum;                     // Magic number which is used to determine which device to send unicast ESPNOW data.
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
     * @brief sends cb
     *
     * @description This function sends the callback to the device of the mac_addr.
     * This function should not be used for long operations but instead a queue should be used.
     * If an esp-idf error occors then this error will be put into the ESP_LOG.
     * 
     * @param
     * mac_addr : uint8_t *
     * status : esp_now_send_status_t //the status of the resieved data that needs to be called back
     */
    static void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status);

    /**
     * @brief recieves cd
     *
     * @description This function resieves the callback data of the device of the mac_addr.
     * And puts the callback data in *data
     * If an esp-idf error occors then this error will be put into the ESP_LOG.
     * 
     * @param
     * mac_addr : uint8_t *
     * data : uint8_t *
     * dataSize : int
     */
    static void recv_cb(const uint8_t *mac_addr, const uint8_t *data, int dataSize);

    /**
     * @brief parses the data
     * 
     * @description This function parses the resieved data from *data to the typedef strukt data_t.
     * By setting al the different variables of data_t with the information of the incomming parameters.
     * If an esp-idf error occors then this error will be put into the ESP_LOG and -1 will be returned.
     *
     * @param
     * data : uint8_t *
     * dataLen : uint16_t
     * state : uint8_t *
     * seq : uint16_t *
     * deviceNum : int *
     * 
     * @return 
     * -1 : int
     * duf->type : uint8_t //see type from data_t
     */
    static int data_parse(uint8_t *data, uint16_t data_len, uint8_t *dataState, uint16_t *dataSeq, int *deviceNum);

    /**
     * @brief prepares data before sending.
     * 
     * @description This function puts the * send_param which is of typedef send_param_t into the typedef data_t so it can be send properly.
     * 
     * @param
     * send_param : send_param_t *
     */
    static void data_prepare(send_param_t *send_param);

    /**
     * @brief Preforms the broadcasting cycle.
     * 
     * @description This function waits till it resieves a callback from the device with the right device number 
     * and if the state of the callback is right the function will send the data.
     * The function also sends callbacks depending on the eventID.
     * If an esp-idf error occors then this error will be put into the ESP_LOG.
     */
    static void task(void *pvParameter);

    /**
     * @brief init for the wifi class
     * 
     * @description This function make the esp module ready for wifi communication.
     * The function claims room on the heap and sends default values.
     * If an esp-idf error occors then this error will be put into the ESP_LOG.
     * 
     * @return
     * ESP_OK : esp_err_t
     * ESP_FAIL : esp_err_t
     */
    static esp_err_t init(void);

    /**
     * @brief deinits the wifi class
     *
     * @description This function delets *send_param objects on the heap and the queue that is made by init.
     *
     * @param
     * send_param : send_param_t *
     */
    static void deinit(send_param_t *send_param);
};

#endif