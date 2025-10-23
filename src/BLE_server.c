/*****************************************************************************
 * File name:  BLE_server.c
 *
 * 
 * Author:    Elizabeth Acevedo
 * 
 * Date:      10/09/2025
 * 
 * Purpose: This program is the server side (Peripheral) of the bluetooth communication 
 *          between my device and the app. The server advertises itself for 
 *          clients (Central) to connect. It exposes a GATT Service containing data 
 *          like sensor readings.
 * 
 * 
 * Utilization: TBD
 *
 * 
 *****************************************************************************/
/** Includes **/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"

// Bluetooth / BLE includes
#include "esp_bt.h"                 // 
#include "esp_bt_main.h"            // initializes and enables Bluetooth stack
#include "esp_gap_ble_api.h"        // handles advertising and connection
#include "esp_gatts_api.h"          // handles GATT server logic (services/characteristics)
#include "esp_gatt_common_api.h"    // general BLE types and constants


#define GATTS_NUM_HANDLE 4

static uint16_t service_handle;
static esp_gatt_srvc_id_t service_id;
static esp_gatt_if_t gatts_if_global;
static esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x40,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

/* FUNCTION PROTOTYPES */
void gatts_event_handler(esp_gatts_cb_event event, esp_garr_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

void app_main() {
    /* Turn on BLE */
    // Initialize NVS 
    nvs_flash_init();   // Stores pairing and bonding info
    

    esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT); // Releases BSS, data for BLE use only after de-initializing
    // Get the default configuration
    esp_bt_controller_config_t bt_cfg = {
        .controller_task_prio = 5,
        .controller_task_stack_size = 4096,
        .mode = ESP_BT_MODE_BLE,
    };
    // Initialize controller
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);
    
    
    esp_bluedroid_init();
    esp_bluedroid_enable();

    /* Create a BLE Device */
    esp_ble_gatts_register_callback(gatts_event_handler);
    esp_ble_gap_register_callback(gap_event_handler);
    esp_ble_gatts_app_register(0);

    /* Create a BLE Server */

    /* Create a BLE Service */
    esp_ble_gatts_create_service(gatts_if, &service_id, GATTS_NUM_HANDLE);

    /* Create a BLE Characteristics */
    esp_ble_gatts_add_char(service_handle, &char_uuid, perm, prop, NULL, NULL);

    /* Create a BLE Descriptor */
    esp_ble_gatts_add_char_descr(service_handle, &descr_uuid, perm, NULL, NULL);

    /* Start Service */
    esp_ble_gatts_start_service(service_handle);

    /* Start Advertising */
    esp_ble_gap_start_advertising(&adv_params);
}

void gatts_event_handler(esp_gatts_cb_event event, esp_garr_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            // Create service
            ESP_LOGI("BLE", "GATT Server Registered");
            break;

        case ESP_GATTS_CONNECT_EVT:
            // Device Connected
            ESP_LOGI("BLE", "Device Connected");
            break;

        case ESP_GATTS_DISCONNECT_EVT:
            // Device disconnected, restart advertising
            ESP_LOGI("BLE", "Device Disconnected");
            esp_ble_gap_start_advertising(&adv_params);
            break;
        default:
            break;
    }
}

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    if (event == ESP_GAP_BLE_ADV_START_COMPLETE_EVT) {
        ESP_LOGI("BLE", "Advertising started");
    }
}

