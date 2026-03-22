// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef UI_SCREEN7_H
#define UI_SCREEN7_H

#ifdef __cplusplus
extern "C" {
#endif

// SCREEN: ui_Screen7
extern void ui_Screen7_screen_init(void);
extern void ui_Screen7_screen_destroy(void);
extern lv_obj_t * ui_Screen7;
extern lv_obj_t * ui_WiFiPanel7;
extern lv_obj_t * ui_Label32;
extern lv_obj_t * ui_BluePanel7;
extern lv_obj_t * ui_Label34;
extern lv_obj_t * ui_blueXPanel7;
extern lv_obj_t * ui_Switch2;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_wifeXPanel7;
extern lv_obj_t * ui_Switch1;
extern lv_obj_t * ui_Label17;

// WiFi和蓝牙设备列表创建函数
extern void ui_create_wifi_device_item(const char *name);
extern void ui_create_bluetooth_device_item(const char *name);

// 设置 Screen7 显示模式：0=WiFi模式，1=蓝牙模式
extern void ui_Screen7_set_mode(int mode);

// CUSTOM VARIABLES

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif