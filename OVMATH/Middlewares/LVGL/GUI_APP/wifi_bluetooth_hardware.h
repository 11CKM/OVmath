// WiFi和蓝牙硬件接口头文件

#ifndef WIFI_BLUETOOTH_HARDWARE_H
#define WIFI_BLUETOOTH_HARDWARE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// 设备列表最大数量
#define MAX_DEVICE_COUNT 10

/**
 * WiFi硬件接口：扫描可用WiFi设备
 * @param devices 设备名称数组（输出）
 * @param count 返回设备数量（输出）
 * @return 扫描是否成功
 */
bool wifi_scan_devices(char devices[][32], int *count);

/**
 * WiFi硬件接口：连接到指定WiFi
 * @param ssid WiFi名称
 * @return 连接是否成功
 */
bool wifi_connect(const char *ssid);

/**
 * WiFi硬件接口：断开WiFi连接
 */
void wifi_disconnect(void);

/**
 * 蓝牙硬件接口：扫描可用蓝牙设备
 * @param devices 设备名称数组（输出）
 * @param count 返回设备数量（输出）
 * @return 扫描是否成功
 */
bool bluetooth_scan_devices(char devices[][32], int *count);

/**
 * 蓝牙硬件接口：连接到指定蓝牙设备
 * @param device_name 设备名称
 * @return 连接是否成功
 */
bool bluetooth_connect(const char *device_name);

/**
 * 蓝牙硬件接口：断开蓝牙连接
 */
void bluetooth_disconnect(void);

#ifdef __cplusplus
}
#endif

#endif
