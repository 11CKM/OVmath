#ifndef __HARDWAREINITTASK_H__
#define __HARDWAREINITTASK_H__

#include "FreeRTOS.h"
#include "task.h"
#define configSUPPORT_DYNAMIC_ALLOCATION 1


void Hardware_Init_Task(void *pvParameters);
void WDOGFeedTask(void *argument);


#endif
