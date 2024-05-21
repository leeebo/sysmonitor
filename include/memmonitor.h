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
 * @brief Dump the memory usage of the current process.
 * 
 */
void memmonitor_dump(void);

/**
 * @brief Dump the detailed memory usage
 * 
 */
void memmonitor_dump_all(void);

#ifdef __cplusplus
}
#endif