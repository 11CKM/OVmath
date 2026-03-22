#ifndef __AHT21_H
#define __AHT21_H

#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "delay.h"

uint8_t AHT_Read_Status(void);
void AHT_Reset(void);
/**
 * @brief 初始化AHT传感器
 * 
 * @return uint8_t 返回初始化状态
 *                 0 - 初始化成功
 *                 非0 - 初始化失败，具体错误码参考硬件手册
 */
uint8_t AHT_Init(void);
uint8_t AHT_Read(float *humi, float *temp);

#endif

