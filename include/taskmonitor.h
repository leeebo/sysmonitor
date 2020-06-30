/*
 * SPDX-FileCopyrightText: 2024 libo_go@163.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Init a timer to statistics the task runtimes.
 * 
 */
void taskmonitor_init();

/**
 * @brief Start the timer to dump the task information.
 * 
 */
void taskmonitor_start();

/**
 * @brief Stop dump the task information.
 * 
 */
void taskmonitor_stop();

/**
 * @brief Deinit the timer.
 * 
 */
void taskmonitor_deinit();

#ifdef __cplusplus
}
#endif