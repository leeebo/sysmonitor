#include "memmonitor.h"
#include "esp_heap_caps.h"
#include "esp_log.h"

const static char *TAG = "MemMonitor";

void memmonitor_dump(void)
{
    ESP_LOGI(TAG,"-----------------Task Dump Start-----------------");
    size_t total = heap_caps_get_total_size(MALLOC_CAP_8BIT);
    size_t free_size = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    printf("Free size of 8bit pool: %zu bytes (total: %zu bytes)\n", free_size, total);
    total = heap_caps_get_total_size(MALLOC_CAP_32BIT);
    free_size = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    printf("Free size of 32bit pool: %zu bytes (total: %zu bytes)\n", free_size, total);
    total = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    free_size = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    printf("Free size of SPI RAM: %zu bytes (total: %zu bytes)\n", free_size, total);
    total = heap_caps_get_total_size(MALLOC_CAP_INTERNAL);
    free_size = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    printf("Free size of internal memory: %zu bytes (total: %zu bytes)\n", free_size, total);
    ESP_LOGI(TAG,"-----------------Task Dump End-----------------");
}

void memmonitor_dump_all(void)
{
    memmonitor_dump();
    heap_caps_dump_all();
    ESP_LOGI(TAG,"---------------Task Dump All End----------------");
}