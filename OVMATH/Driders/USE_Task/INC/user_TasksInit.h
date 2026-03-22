#ifndef __USER_TASKSINIT_H__
#define __USER_TASKSINIT_H__

#include "FreeRTOS.h"
#include "task.h"
#include "HardwareInitTask.h"
#include "Lvgl_task.h"
#include "queue.h"
#include "stdio.h"
#include "delay.h"
#include "lvgl.h"

#define configSUPPORT_DYNAMIC_ALLOCATION 1

extern QueueHandle_t IdQueue;

void user_TasksInit(void);




#endif
