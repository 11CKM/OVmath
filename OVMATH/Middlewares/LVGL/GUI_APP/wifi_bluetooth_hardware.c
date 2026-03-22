// WiFi和蓝牙硬件模拟接口
// 用户需要根据实际硬件替换这些函数的实现

#include <string.h>
#include <stdbool.h>

/**
 * WiFi硬件接口：扫描可用WiFi设备
 * @param devices 设备名称数组
 * @param count 返回设备数量
 * @return 扫描是否成功
 */
bool wifi_scan_devices(char devices[][32], int *count)
{
    // 模拟数据：返回几个WiFi设备
    strcpy(devices[0], "Home_WiFi_5G");
    strcpy(devices[1], "Office_Network");
    strcpy(devices[2], "Guest_WiFi");
    strcpy(devices[3], "Coffee_Shop_Free");
    *count = 4;
    return true;
}

/**
 * WiFi硬件接口：连接到指定WiFi
 * @param ssid WiFi名称
 * @return 连接是否成功
 */
bool wifi_connect(const char *ssid)
{
    // 模拟：总是返回成功
    // 实际实现：调用硬件API连接WiFi
    return true;
}

/**
 * WiFi硬件接口：断开WiFi连接
 */
void wifi_disconnect(void)
{
    // 模拟：什么都不做
    // 实际实现：调用硬件API断开连接
}

/**
 * 蓝牙硬件接口：扫描可用蓝牙设备
 * @param devices 设备名称数组
 * @param count 返回设备数量
 * @return 扫描是否成功
 */
bool bluetooth_scan_devices(char devices[][32], int *count)
{
    // 模拟数据：返回几个蓝牙设备
    strcpy(devices[0], "Headphones_Pro");
    strcpy(devices[1], "Smart_Watch_Series6");
    strcpy(devices[2], "Car_Audio_System");
    strcpy(devices[3], "Wireless_Mouse");
    *count = 4;
    return true;
}

/**
 * 蓝牙硬件接口：连接到指定蓝牙设备
 * @param device_name 设备名称
 * @return 连接是否成功
 */
bool bluetooth_connect(const char *device_name)
{
    // 模拟：总是返回成功
    // 实际实现：调用硬件API连接蓝牙设备
    return true;
}

/**
 * 蓝牙硬件接口：断开蓝牙连接
 */
void bluetooth_disconnect(void)
{
    // 模拟：什么都不做
    // 实际实现：调用硬件API断开连接
}
