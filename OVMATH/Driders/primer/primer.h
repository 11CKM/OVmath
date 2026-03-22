#ifndef  _PRIMER_H_
#define  _PRIMER_H_

#include "stm32f4xx_hal.h"


void POWER_EN(void);
void POWER_END(void);
uint8_t ChargeCheck(void);
float  PowerSize(void);
float  PowerSize_8Times(void);
uint8_t PowerCalculate(void);
void POWER_INIT(void);
#endif
