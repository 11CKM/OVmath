#include "delay.h"

// FreeRTOS related variables
volatile uint8_t delay_osrunning = 0;
volatile uint8_t delay_osintnesting = 0;
uint16_t fac_ms = 1;

/**
 * @brief 锁定任务调度器
 *
 * 该函数通过调用FreeRTOS的vTaskSuspendAll()函数来暂停所有任务调度，
 * 确保在延时操作期间不会发生任务切换。
 *
 * @note 在延时操作完成后必须调用delay_osschedunlock()来恢复任务调度
 */
void delay_osschedlock(void)
{
	vTaskSuspendAll();
}

/**
 * @brief 恢复任务调度器
 *
 * 该函数是FreeRTOS中xTaskResumeAll()的封装，用于恢复之前被暂停的任务调度器。
 * 通常在延时函数中与delay_osschedlock()配对使用，确保微秒级延时期间不会被任务切换打断。
 *
 * @note 必须在调用delay_osschedlock()后调用本函数，否则可能导致系统调度异常
 * @see delay_osschedlock()
 */
void delay_osschedunlock(void)
{
	xTaskResumeAll();
}

/**
 * @brief  FreeRTOS任务延时函数
 *
 * @param ticks  需要延时的系统节拍数
 *
 * @note   该函数是对FreeRTOS的vTaskDelay的简单封装
 *         用于在操作系统环境下实现任务级延时
 *         延时期间会主动让出CPU给其他任务
 */
void delay_ostimedly(uint32_t ticks)
{
	vTaskDelay(ticks);
}

void Systick_Init(void)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq));
}

#if OS_SUPPORT   //FreeRtos的函数
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;
	ticks=nus*100;
	delay_osschedlock();
	told=SysTick->VAL;
	while(1)
	{
		tnow=SysTick->VAL;
		if(tnow!=told)
		{
			if(tnow<told)tcnt+=told-tnow;//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;
		}
	};
	delay_osschedunlock();
}

void delay_ms(uint32_t nms)
{
	if(delay_osrunning&&delay_osintnesting==0)
	{
		if(nms>=fac_ms)
		{
   			delay_ostimedly(nms/fac_ms);
		}
		nms%=fac_ms;
	}
	delay_us((uint32_t)(nms*1000));
}

#else

void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;
	ticks=nus*100;
	told=SysTick->VAL;
	while(1)
	{
		tnow=SysTick->VAL;
		if(tnow!=told)
		{
			if(tnow<told)tcnt+=told-tnow;
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;
		}
	}
}

void delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}

#endif
