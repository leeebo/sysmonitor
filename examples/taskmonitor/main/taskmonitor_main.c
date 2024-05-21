/*
 * SPDX-FileCopyrightText: 2024 libo_go@163.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "taskmonitor.h"
#include "memmonitor.h"

#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
#include "esp_spi_flash.h"
#else
#include "esp_chip_info.h"
#include "esp_flash.h"
#endif

void app_main(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    unsigned major_rev = chip_info.full_revision / 100;
    unsigned minor_rev = chip_info.full_revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
#else
    uint32_t flash_size = 0;
    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }
    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
#endif
    memmonitor_dump_all();
    /* Print task information */
    taskmonitor_init();
    taskmonitor_start();

    while (1) {
        for (int i = 0; i < 1000000; i++) {
            asm volatile ("nop");
        }
        vTaskDelay(1);
    }

    /* won't reach here */
    taskmonitor_stop();
    taskmonitor_deinit();
}