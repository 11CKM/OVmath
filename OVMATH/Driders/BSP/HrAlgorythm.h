#ifndef __HRALGORYTHM_H__
#define __HRALGORYTHM_H__

#include "main.h"
#include "useQueur.h"

void HR_AlgoInit(void);
//心率计算核心函数
uint16_t HR_Calculate(uint16_t present_dat,uint32_t present_time);


#endif
