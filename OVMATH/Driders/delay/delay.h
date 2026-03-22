#ifndef  _DELAY_H_
#define  _DELAY_H_

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
//是否使用操作系统的延时函数标志位，1为使用，0为使用其他延时
#define OS_SUPPORT 	1

void Systick_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

// FreeRTOS delay functions
extern volatile uint8_t delay_osrunning;
extern volatile uint8_t delay_osintnesting;
extern uint16_t fac_ms;

void delay_osschedlock(void);
void delay_osschedunlock(void);
void delay_ostimedly(uint32_t ticks);

#endif
