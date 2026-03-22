#include "CST816.h"
#include "stm32f4xx_hal.h"
#include "delay.h"

#define TOUCH_OFFSET_Y 0

// 触摸点实例
CST816_Info CST816_Instance;

// I2C总线定义
IIC_Pin CST816_Bus = {
    .II2C_SDA_PORT = GPIOB,
    .II2C_SCL_PORT = GPIOB,
    .IIC_PIN_SDA   = GPIO_PIN_4,
    .IIC_PIN_SCL   = GPIO_PIN_6,
};

/******************************************************************************
  函数说明：CST816 GPIO初始化
******************************************************************************/
void CST816_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 复位引脚
    GPIO_InitStruct.Pin = TOUCH_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(TOUCH_RST_PORT, &GPIO_InitStruct);

    // 默认高电平
    TOUCH_RST_1();

    // I2C引脚初始化
    IIC_Init(&CST816_Bus);
}

/******************************************************************************
  函数说明：CST816完整初始化
******************************************************************************/
void CST816_Init(void)
{
    CST816_GPIO_Init();
    CST816_Config_AutoSleepTime(5);  // 5秒无触摸自动休眠
}

/******************************************************************************
  函数说明：读取单个寄存器
******************************************************************************/
uint8_t CST816_ReadReg(uint8_t reg_addr)
{
    return IIC_Read_One_Byte(&CST816_Bus, CST816_ADDR, reg_addr);
}

/******************************************************************************
  函数说明：写入单个寄存器
******************************************************************************/
void CST816_WriteReg(uint8_t reg_addr, uint8_t data)
{
    IIC_Write_One_Byte(&CST816_Bus, CST816_ADDR, reg_addr, data);
}

/******************************************************************************
  函数说明：读取触摸坐标
******************************************************************************/
void CST816_Get_XY(void)
{
    uint8_t data[4];

    IIC_Read_Multi_Byte(&CST816_Bus, CST816_ADDR, CST816_X_POS_H, 4, data);

    // 组合坐标 (X: 12位, Y: 12位)
    CST816_Instance.X_Pos = ((data[0] & 0x0F) << 8) | data[1];
    CST816_Instance.Y_Pos = ((data[2] & 0x0F) << 8) | data[3] + TOUCH_OFFSET_Y;
}

/******************************************************************************
  函数说明：获取触摸点数量
******************************************************************************/
uint8_t CST816_Get_FingerNum(void)
{
    return CST816_ReadReg(CST816_FINGER_NUM);
}

/******************************************************************************
  函数说明：获取手势ID
******************************************************************************/
uint8_t CST816_Get_GestureID(void)
{
    return CST816_ReadReg(CST816_GESTURE_ID);
}

/******************************************************************************
  函数说明：硬件复位
******************************************************************************/
void CST816_Reset(void)
{
    TOUCH_RST_0();
    delay_ms(10);
    TOUCH_RST_1();
    delay_ms(100);
}

/******************************************************************************
  函数说明：进入睡眠模式
******************************************************************************/
void CST816_Sleep(void)
{
    CST816_WriteReg(CST816_SLEEP_MODE, 0x03);
}

/******************************************************************************
  函数说明：唤醒触摸屏
******************************************************************************/
void CST816_Wakeup(void)
{
    CST816_Reset();
}

/******************************************************************************
  函数说明：配置自动休眠时间
******************************************************************************/
void CST816_Config_AutoSleepTime(uint8_t time)
{
    CST816_WriteReg(CST816_AUTO_SLEEP, time);
}
