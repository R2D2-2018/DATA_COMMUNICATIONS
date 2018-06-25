/* ESPNOW Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "wifi.hpp"

/*
   This example shows how to use ESPNOW.
   Prepare two device, one for sending ESPNOW data and another for receiving
   ESPNOW data.
*/

static const char *TAG = "wifi";

static xQueueHandle queue;

static uint8_t broadcast_mac[ESP_NOW_ETH_ALEN]        = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint16_t s_seq[DATA_MAX] = {0, 0};

/* WiFi should start before using ESPNOW */
Wifi::Wifi() {
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE));
    ESP_ERROR_CHECK(esp_wifi_start());

    /* In order to simplify example, channel is set after WiFi started.
     * This is not necessary in real application if the two devices have
     * been already on the same channel.
     */
    ESP_ERROR_CHECK(esp_wifi_set_channel(CONFIG_ESPNOW_CHANNEL, wifi_second_chan_t::WIFI_SECOND_CHAN_NONE));
}

esp_err_t Wifi::event_handler(void *ctx, system_event_t *event) {
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        ESP_LOGI(TAG, "WiFi started");
        break;
    default:
        break;
    }
    return ESP_OK;
}

/* ESPNOW sending or receiving callback function is called in WiFi task.
 * Users should not do lengthy operations from this task. Instead, post
 * necessary data to a queue and handle it from a lower priority task. */
void Wifi::send_cb(const uint8_t *mac_addr, esp_now_send_status_t status) {
    event_t evt;
    event_send_cb_t *send_cb = &evt.info.send_cb;

    if (mac_addr == NULL) {
        ESP_LOGE(TAG, "Send cb arg error");
        return;
    }

    evt.id = SEND_CB;
    memcpy(send_cb->mac_addr, mac_addr, ESP_NOW_ETH_ALEN);
    send_cb->status = status;
    if (xQueueSend(queue, &evt, portMAX_DELAY) != pdTRUE) {
        ESP_LOGW(TAG, "Send send queue fail");
    }
}

void Wifi::recv_cb(const uint8_t *mac_addr, const uint8_t *data, int dataSize) {
    event_t evt;
    event_recv_cb_t *recv_cb = &evt.info.recv_cb;

    if (mac_addr == NULL || data == NULL || dataSize <= 0) {
        ESP_LOGE(TAG, "Receive cb arg error");
        return;
    }

    evt.id = RECV_CB;
    memcpy(recv_cb->mac_addr, mac_addr, ESP_NOW_ETH_ALEN);
    recv_cb->data = new uint8_t(dataSize);
    if (recv_cb->data == NULL) {
        ESP_LOGE(TAG, "Malloc receive data fail");
        return;
    }
    memcpy(recv_cb->data, data, dataSize);
    recv_cb->data_len = dataSize;
    if (xQueueSend(queue, &evt, portMAX_DELAY) != pdTRUE) {
        ESP_LOGW(TAG, "Send receive queue fail");
        delete recv_cb->data;
    }
}

int Wifi::data_parse(uint8_t *data, uint16_t dataLen, uint8_t * state, uint16_t * seq, int * deviceNum) {
    data_t *buf = (data_t *)data;
    uint16_t crc, crc_cal = 0;

    if (dataLen < sizeof(data_t)) {
        ESP_LOGE(TAG, "Receive wifi data too short, len:%d", dataLen);
        return -1;
    }

    *state   = buf->state;
    *seq     = buf->seq_num;
    *deviceNum   = buf->deviceNum;
    crc      = buf->crc;
    buf->crc = 0;
    crc_cal  = crc16_le(UINT16_MAX, (uint8_t const *)buf, dataLen);

    if (crc_cal == crc) {
        return buf->type;
    }

    return -1;
}

void Wifi::data_prepare(send_param_t *send_param) {
    data_t *buf = (data_t *)send_param->buffer;
    int i                      = 0;

    assert(send_param->len >= sizeof(data_t));

    buf->type    = IS_BROADCAST_ADDR(send_param->dest_mac) ? DATA_BROADCAST : DATA_UNICAST;
    buf->state   = send_param->state;
    buf->seq_num = s_seq[buf->type]++;
    buf->crc     = 0;
    buf->deviceNum   = send_param->deviceNum;
    for (i = 0; i < send_param->len - sizeof(data_t); i++) {
        buf->payload[i] = (uint8_t)esp_random();
    }
    buf->crc = crc16_le(UINT16_MAX, (uint8_t const *)buf, send_param->len);
}

void Wifi::task(void *pvParameter) {
    event_t evt;
    uint8_t recv_state = 0;
    uint16_t recv_seq  = 0;
    int recv_deviceNum    = 0;
    bool is_broadcast  = false;
    int ret;

    vTaskDelay(5000 / portTICK_RATE_MS);
    ESP_LOGI(TAG, "Start sending broadcast data");

    /* Start sending broadcast ESPNOW data. */
    send_param_t *send_param = (send_param_t *)pvParameter;
    if (esp_now_send(send_param->dest_mac, send_param->buffer, send_param->len) != ESP_OK) {
        ESP_LOGE(TAG, "Send error");
        deinit(send_param);
        vTaskDelete(NULL);
    }

    while (xQueueReceive(queue, &evt, portMAX_DELAY) == pdTRUE) {
        switch (evt.id) {
        case SEND_CB: {
            event_send_cb_t *send_cb = &evt.info.send_cb;
            is_broadcast                            = IS_BROADCAST_ADDR(send_cb->mac_addr);

            ESP_LOGD(TAG, "Send data to " MACSTR ", status1: %d", MAC2STR(send_cb->mac_addr), send_cb->status);

            if (is_broadcast && (send_param->broadcast == false)) {
                break;
            }

            if (!is_broadcast) {
                send_param->count--;
                if (send_param->count == 0) {
                    ESP_LOGI(TAG, "Send done");
                    deinit(send_param);
                    vTaskDelete(NULL);
                }
            }

            /* Delay a while before sending the next data. */
            if (send_param->delay > 0) {
                vTaskDelay(send_param->delay / portTICK_RATE_MS);
            }

            ESP_LOGI(TAG, "send data to " MACSTR "", MAC2STR(send_cb->mac_addr));

            memcpy(send_param->dest_mac, send_cb->mac_addr, ESP_NOW_ETH_ALEN);
            data_prepare(send_param);

            /* Send the next data after the previous data is sent. */
            if (esp_now_send(send_param->dest_mac, send_param->buffer, send_param->len) != ESP_OK) {
                ESP_LOGE(TAG, "Send error");
                deinit(send_param);
                vTaskDelete(NULL);
            }
            break;
        }
        case RECV_CB: {
            event_recv_cb_t *recv_cb = &evt.info.recv_cb;

            ret = data_parse(recv_cb->data, recv_cb->data_len, &recv_state, &recv_seq, &recv_deviceNum);
            delete recv_cb->data;
            if (ret == DATA_BROADCAST) {
                ESP_LOGI(TAG, "Receive %dth broadcast data from: " MACSTR ", len: %d", recv_seq, MAC2STR(recv_cb->mac_addr),
                         recv_cb->data_len);

                /* If MAC address does not exist in peer list, add it to peer list. */
                if (esp_now_is_peer_exist(recv_cb->mac_addr) == false) {
                    esp_now_peer_info_t *peer = new esp_now_peer_info_t[sizeof(esp_now_peer_info_t)];

                    if (peer == NULL) {
                        ESP_LOGE(TAG, "Malloc peer information fail");
                        deinit(send_param);
                        vTaskDelete(NULL);
                    }
                    memset(peer, 0, sizeof(esp_now_peer_info_t));
                    peer->channel = CONFIG_ESPNOW_CHANNEL;
                    peer->ifidx   = WIFI_IF;
                    peer->encrypt = true;
                    memcpy(peer->lmk, CONFIG_ESPNOW_LMK, ESP_NOW_KEY_LEN);
                    memcpy(peer->peer_addr, recv_cb->mac_addr, ESP_NOW_ETH_ALEN);
                    ESP_ERROR_CHECK(esp_now_add_peer(peer));
                    delete[] peer;
                }

                /* Indicates that the device has received broadcast ESPNOW data. */
                if (send_param->state == 0) {
                    send_param->state = 1;
                }

                /* If receive broadcast ESPNOW data which indicates that the other
                 * device has received broadcast ESPNOW data and the local deviceNum number
                 * is bigger than that in the received broadcast ESPNOW data, stop
                 * sending broadcast ESPNOW data and start sending unicast ESPNOW data.
                 */
                if (recv_state == 1) {
                    /* The device which has the bigger deviceNum number sends ESPNOW data, the
                     * other one receives ESPNOW data.
                     */
                    if (send_param->unicast == false && send_param->deviceNum >= recv_deviceNum) {
                        ESP_LOGI(TAG, "Start sending unicast data");
                        ESP_LOGI(TAG, "send data to " MACSTR "", MAC2STR(recv_cb->mac_addr));

                        /* Start sending unicast ESPNOW data. */
                        memcpy(send_param->dest_mac, recv_cb->mac_addr, ESP_NOW_ETH_ALEN);
                        data_prepare(send_param);
                        if (esp_now_send(send_param->dest_mac, send_param->buffer, send_param->len) != ESP_OK) {
                            ESP_LOGE(TAG, "Send error");
                            deinit(send_param);
                            vTaskDelete(NULL);
                        } else {
                            send_param->broadcast = false;
                            send_param->unicast   = true;
                        }
                    }
                }
            } else if (ret == DATA_UNICAST) {
                ESP_LOGI(TAG, "Receive %dth unicast data from: " MACSTR ", len: %d", recv_seq, MAC2STR(recv_cb->mac_addr),
                         recv_cb->data_len);

                /* If receive unicast ESPNOW data, also stop sending broadcast ESPNOW
                 * data. */
                send_param->broadcast = false;
            } else {
                ESP_LOGI(TAG, "Receive error data from: " MACSTR "", MAC2STR(recv_cb->mac_addr));
            }
            break;
        }
        default:
            ESP_LOGE(TAG, "Callback type error: %d", evt.id);
            break;
        }
    }
}

esp_err_t Wifi::init(void) {
    send_param_t *send_param;

    queue = xQueueCreate(QUEUE_SIZE, sizeof(event_t));
    if (queue == NULL) {
        ESP_LOGE(TAG, "Create mutex fail");
        return ESP_FAIL;
    }

    /* Initialize ESPNOW and register sending and receiving callback function. */
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(send_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(recv_cb));

    /* Set primary master key. */
    ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t *)CONFIG_ESPNOW_PMK));

    /* Add broadcast peer information to peer list. */
    esp_now_peer_info_t *peer = new esp_now_peer_info_t[sizeof(esp_now_peer_info_t)];

    if (peer == NULL) {
        ESP_LOGE(TAG, "Malloc peer information fail");
        vSemaphoreDelete(queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    memset(peer, 0, sizeof(esp_now_peer_info_t));
    peer->channel = CONFIG_ESPNOW_CHANNEL;
    peer->ifidx   = WIFI_IF;
    peer->encrypt = false;
    memcpy(peer->peer_addr, broadcast_mac, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK(esp_now_add_peer(peer));

    delete[] peer;

    /* Initialize sending parameters. */
    send_param = new send_param_t[sizeof(send_param_t)];

    memset(send_param, 0, sizeof(send_param_t));
    if (send_param == NULL) {
        ESP_LOGE(TAG, "Malloc send parameter fail");
        vSemaphoreDelete(queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    send_param->unicast   = false;
    send_param->broadcast = false;
    send_param->state     = 0;
    send_param->deviceNum     = esp_random();
    send_param->count     = CONFIG_ESPNOW_SEND_COUNT;
    send_param->delay     = CONFIG_ESPNOW_SEND_DELAY;
    send_param->len       = CONFIG_ESPNOW_SEND_LEN;
    send_param->buffer    = new uint8_t(CONFIG_ESPNOW_SEND_LEN);
    if (send_param->buffer == NULL) {
        ESP_LOGE(TAG, "Malloc send buffer fail");
        delete[] send_param;
        vSemaphoreDelete(queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    memcpy(send_param->dest_mac, broadcast_mac, ESP_NOW_ETH_ALEN);
    data_prepare(send_param);

    xTaskCreate(task, "task", 2048, send_param, 4, NULL);

    return ESP_OK;
}

void Wifi::deinit(send_param_t *send_param) {
    delete send_param->buffer;
    delete send_param;
    vSemaphoreDelete(queue);
    esp_now_deinit();
}
