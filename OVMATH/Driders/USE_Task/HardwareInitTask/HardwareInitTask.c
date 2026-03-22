#include "HardwareInitTask.h"

// includes
// sys
#include "usart.h"
#include "tim.h"
#include "stm32f4xx_it.h"

// user
#include "user_TasksInit.h"

// bsp
#include "key.h"
#include "lcd.h"
#include "CST816.h"
#include "DataSava.h"
#include "delay.h"
#include "AHT21.h"
#include "LSM303.h"
#include "SPL06-001.h"
#include "MPU6050.h"
#include "BL24C02.h"
#include "KT6368A.h"

// ui
//gui
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "ui.h"

// APP SYS setting

// 全局变量
uint8_t HardInt_receive_str[25];

/**
 * @brief  hardwares init task
 * @param  argument: Not used
 * @retval None
 */
void Hardware_Init_Task(void *argument)
{
    while(1)
    {
        vTaskSuspendAll();
        // RTC Wake
        if(HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 2000, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
        {
           Error_Handler();
        }
        // usart start
        HAL_UART_Receive_DMA(&huart1,(uint8_t*)HardInt_receive_str,25);
        __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);

        // PWM Start
        HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);

        // sys delay
        Systick_Init();

        // key
        Key_Port_Init();

        // touch
        CST816_GPIO_Init();
        CST816_Init();

        // lcd
        LCD_Init();
        LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);

        // sensors
        uint8_t num = 3;
        while(num && AHT_Init())
        {
            num--;
            delay_ms(100);
        }

        num = 3;
        while(num && LSM303DLH_Init())
        {
            num--;
            delay_ms(100);
        }
        if(!LSM303DLH_Init())
            LSM303DLH_Sleep();

        num = 3;
        while(num && SPL_init())
        {
            num--;
            delay_ms(100);
        }

        num = 3;
        while(num && MPU_Init())
        {
            num--;
            delay_ms(100);
        }

        // EEPROM
        BL24C02_Init();

        // BLE
        KT6328_GPIO_Init();
        KT6328_Disable();
        // ui
        // LVGL init
        lv_init();
        // 初始化LVGL显示驱动
        lv_port_disp_init();
        // 初始化LVGL输入设备
        lv_port_indev_init();
        // 初始化UI
        ui_init();

        xTaskResumeAll();
        vTaskDelete(NULL);
    }
}

//看门狗任务
void WDOGFeedTask(void *argument)
{
	//owdg
  WDOG_Port_Init();
  while(1)
  {
		WDOG_Feed();
		WDOG_Enable();
    delay_ms(100);
  }
}


