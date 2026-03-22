#ifndef __CST816_H
#define __CST816_H

#include "stdint.h"
#include "I2C.h"

// CST816 引脚定义
#define TOUCH_RST_PIN   GPIO_PIN_15
#define TOUCH_RST_PORT  GPIOA
#define TOUCH_INT_PIN   GPIO_PIN_1
#define TOUCH_INT_PORT  GPIOB

// 触摸屏操作宏
#define TOUCH_RST_0()  HAL_GPIO_WritePin(TOUCH_RST_PORT, TOUCH_RST_PIN, GPIO_PIN_RESET)
#define TOUCH_RST_1()  HAL_GPIO_WritePin(TOUCH_RST_PORT, TOUCH_RST_PIN, GPIO_PIN_SET)

// CST816设备地址
#define CST816_ADDR    0x15

// CST816寄存器地址定义
#define CST816_GESTURE_ID    0x01
#define CST816_FINGER_NUM    0x02
#define CST816_X_POS_H      0x03
#define CST816_X_POS_L      0x04
#define CST816_Y_POS_H      0x05
#define CST816_Y_POS_L      0x06
#define CST816_CHIP_ID       0xA7
#define CST816_SLEEP_MODE    0xE5
#define CST816_MOTION_MASK   0xEC
#define CST816_AUTO_SLEEP    0xF9

// 触摸点信息结构体
typedef struct {
    uint16_t X_Pos;
    uint16_t Y_Pos;
} CST816_Info;

// 手势ID枚举
typedef enum {
    NO_GESTURE = 0x00,
    GLIDE_DOWN = 0x01,
    GLIDE_UP   = 0x02,
    GLIDE_LEFT = 0x03,
    GLIDE_RIGHT= 0x04,
    CLICK      = 0x05,
    DOUBLE_CLICK= 0x0B,
    LONG_PRESS = 0x0C,
} CST816_GestureID;

// 初始化函数
void CST816_Init(void);
void CST816_GPIO_Init(void);

// 数据读取函数
void CST816_Get_XY(void);
uint8_t CST816_Get_FingerNum(void);
uint8_t CST816_Get_GestureID(void);

// 配置函数
void CST816_Sleep(void);
void CST816_Wakeup(void);
void CST816_Config_AutoSleepTime(uint8_t time);

// 外部变量声明
extern CST816_Info CST816_Instance;

#endif
