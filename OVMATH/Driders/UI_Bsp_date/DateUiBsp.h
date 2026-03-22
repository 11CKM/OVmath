#ifndef __DATE_UI_BSP_H__
#define __DATE_UI_BSP_H__

#include "stdint.h"
#include <stdbool.h>
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "AHT21.h"
#include "SPL06-001.h"
#include "LSM303.h"
#include "em70x8.h"
#include "KT6368A.h"
#include "lcd.h"
#include "primer.h"
#include "rtc.h"

// 时间和日期结构体
typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t weekday;
} DateTime_t;

// 函数声明
void DateUiBsp_Init(void);
void DateUiBsp_GetDateTime(DateTime_t *datetime);
void DateUiBsp_UpdateTimeUI(void);
void DateUiBsp_UpdateDateUI(void);
void DateUiBsp_UpdateDateTimeUI(void);

#endif