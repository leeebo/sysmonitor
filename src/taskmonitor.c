/*
 * SPDX-FileCopyrightText: 2024 libo_go@163.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"
#include "taskmonitor.h"

#define M2T(X) ((unsigned int)(X)/ portTICK_PERIOD_MS)
#define TASK_MAX_COUNT CONFIG_TASKMONITOR_MAX_TASKS
#define DUMP_INTERVAL (CONFIG_TASKMONITOR_DUMP_INTERVAL * 1000)

const static char *TAG = "TaskMonitor";
static void task_monitor_cb(TimerHandle_t timer);

typedef struct {
    uint32_t ulRunTimeCounter;
    uint32_t xTaskNumber;
} task_data_t;

static task_data_t previous_snapshot[TASK_MAX_COUNT];
static int task_top_id = 0;
static uint32_t total_runtime = 0;
static StaticTimer_t timer_stack;
static bool initialized = false; //singleton
static TimerHandle_t timer;

void taskmonitor_init()
{
	if (initialized) {
        return;
    }
    timer = xTimerCreateStatic("taskMonitor", M2T(DUMP_INTERVAL), pdTRUE, NULL, task_monitor_cb, &timer_stack);
    initialized = true;
}

void taskmonitor_deinit()
{
    if (!initialized) {
        return;
    }
    xTimerDelete(timer, 100);
    initialized = false;
}

void taskmonitor_start(){
	if (!initialized) {
        return;
    }
	xTimerStart(timer, 100);
}

void taskmonitor_stop(){
	if (!initialized) {
        return;
    }
	xTimerStop(timer, 100);
}

static task_data_t *getPreviousTaskData(uint32_t xTaskNumber)
{
    // Try to find the task in the list of tasks
    for (int i = 0; i < task_top_id; i++) {
        if (previous_snapshot[i].xTaskNumber == xTaskNumber) {
            return &previous_snapshot[i];
        }
    }
    // Allocate a new entry
    assert(task_top_id < TASK_MAX_COUNT);
    task_data_t *result = &previous_snapshot[task_top_id];
    result->xTaskNumber = xTaskNumber;
    task_top_id++;
    return result;   
}

static void task_monitor_cb(TimerHandle_t timer)
{
    uint32_t totalRunTime = 0;
    TaskStatus_t taskStats[TASK_MAX_COUNT] = {0};
    uint32_t taskCount = uxTaskGetSystemState(taskStats, TASK_MAX_COUNT, &totalRunTime);
    assert(task_top_id < TASK_MAX_COUNT);
    uint32_t totalDelta = totalRunTime - total_runtime;
    float f = 100.0 / totalDelta;

    ESP_LOGI(TAG,"-----------------Task Dump Start-----------------");
    printf("|Load\tStack left\tName\t\tPRI|\n");

    for (uint32_t i = 0; i < taskCount; i++) {
        TaskStatus_t *stats = &taskStats[i];
        task_data_t *previousTaskData = getPreviousTaskData(stats->xTaskNumber);
        uint32_t taskRunTime = stats->ulRunTimeCounter;
        float load = f * (taskRunTime - previousTaskData->ulRunTimeCounter);
        printf("|%.2f\t%" PRIu32 "\t\t%s\t\t%u|\n", load, stats->usStackHighWaterMark, stats->pcTaskName, stats->uxBasePriority);
        previousTaskData->ulRunTimeCounter = taskRunTime;
    }
    ESP_LOGI(TAG,"Total Free heap: %" PRIu32 "", esp_get_free_heap_size());
    ESP_LOGI(TAG,"-----------------Task Dump End-------------------");
    total_runtime = totalRunTime;
}
