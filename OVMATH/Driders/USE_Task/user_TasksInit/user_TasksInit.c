#include "user_TasksInit.h"
//句柄
TaskHandle_t WDOG_handle;                //看门狗句柄
TaskHandle_t hardware_task_handler;      // 硬件初始化任务句柄
TaskHandle_t start_task_handler;         // 启动任务句柄
TaskHandle_t ID_task_handle;             // 触摸任务句柄


//队列
IdQueue=xQueueCreate(1,sizeof(uint8_t));//触摸时间数据队列


//函数
void Start_Task(void *pvParameters);  // 启动任务函数声明




void user_TasksInit(void)
{
    // 创建启动任务
    xTaskCreate((TaskFunction_t)Start_Task,        // 任务函数
                (char *)"Start_Task",              // 任务名称
                (configSTACK_DEPTH_TYPE)128,       // 堆栈大小
                (void *)NULL,                      // 任务参数
                (UBaseType_t) 1,                   // 优先级
                (TaskHandle_t *)&start_task_handler); // 任务句柄
                
    vTaskStartScheduler();  // 启动任务调度器
}



void Start_Task( void * pvParameters )
{
    taskENTER_CRITICAL();  // 【1】进入临界区（关中断）
    // 创建 硬件初始化任务
    xTaskCreate((TaskFunction_t)Hardware_Init_Task,
                (char *)"Hardware_Init_Task",
                (configSTACK_DEPTH_TYPE)320,
                (void *)NULL,
                (UBaseType_t)3,
                (TaskHandle_t *)&hardware_task_handler);   
    //看门狗任务
    xTaskCreate((TaskFunction_t)WDOGFeedTask,
                (char *)"WDOGFeedTask",
                (configSTACK_DEPTH_TYPE)320,
                (void *)NULL,
                (UBaseType_t)3,
                (TaskHandle_t *)&WDOG_handle); 
    //LVGL触摸任务
    xTaskCreate((TaskFunction_t)Lvgl_task,
                (char *)"Lvgl_task",
                (configSTACK_DEPTH_TYPE)320,
                (void *)IdQueue,
                (UBaseType_t)2,
                (TaskHandle_t *)&ID_task_handle); 
    
    vTaskDelete(NULL);     // 【2】删除自己（Start_Task）
    taskEXIT_CRITICAL();   // 【3】退出临界区（开中断）
}





