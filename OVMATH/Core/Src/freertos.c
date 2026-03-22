/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    freertos.c
  * @brief   Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook( void );
void vApplicationTickHook( void );
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */

  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */

  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */

  /* USER CODE BEGIN RTOS_THREADS */

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */

  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN 4 */

/**
  * @brief  Provide the idle task memory
  * @param  ppxIdleTaskTCBBuffer: pointer to the idle task TCB buffer
  * @param  ppxIdleTaskStackBuffer: pointer to the idle task stack buffer
  * @param  pulIdleTaskStackSize: pointer to the idle task stack size
  * @retval None
  */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
  /* USER CODE BEGIN GET_IDLE_TASK_MEMORY */

  /* Allocate the memory for the Idle Task TCB and Stack */
  static StaticTask_t xIdleTaskTCBBuffer;
  static StackType_t uxIdleTaskStackBuffer[ configMINIMAL_STACK_SIZE ];

  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = uxIdleTaskStackBuffer;
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;

  /* USER CODE END GET_IDLE_TASK_MEMORY */
}

/**
  * @brief  Provide the timer task memory
  * @param  ppxTimerTaskTCBBuffer: pointer to the timer task TCB buffer
  * @param  ppxTimerTaskStackBuffer: pointer to the timer task stack buffer
  * @param  pulTimerTaskStackSize: pointer to the timer task stack size
  * @retval None
  */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
  /* USER CODE BEGIN GET_TIMER_TASK_MEMORY */

  /* Allocate the memory for the Timer Task TCB and Stack */
  static StaticTask_t xTimerTaskTCBBuffer;
  static StackType_t uxTimerTaskStackBuffer[ configTIMER_TASK_STACK_DEPTH ];

  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = uxTimerTaskStackBuffer;
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;

  /* USER CODE END GET_TIMER_TASK_MEMORY */
}

/**
  * @brief  Hook function for the idle task
  * @param  None
  * @retval None
  */
void vApplicationIdleHook( void )
{
  /* USER CODE BEGIN IDLE_HOOK */

  /* This hook function is called by the idle task.
     You can add low power mode or other background tasks here. */

  /* USER CODE END IDLE_HOOK */
}

/**
  * @brief  Hook function for the tick interrupt
  * @param  None
  * @retval None
  */
void vApplicationTickHook( void )
{
  /* USER CODE BEGIN TICK_HOOK */

  /* This hook function is called from the tick interrupt.
     You can add periodic tasks here. */

  /* USER CODE END TICK_HOOK */
}

/* USER CODE END 4 */
