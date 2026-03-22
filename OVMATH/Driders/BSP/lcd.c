#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "delay.h"
#include "spi.h"
#include "tim.h"

// LCD引脚定义
#define SCLK_PORT      GPIOB      // SPI时钟引脚端口 (硬件SPI1_SCK)
#define SCLK_PIN       GPIO_PIN_3 // SPI时钟引脚 (PB3)

#define MOSI_PORT      GPIOB      // SPI数据输出引脚端口 (硬件SPI1_MOSI)
#define MOSI_PIN       GPIO_PIN_5 // SPI数据输出引脚 (PB5)

#define RES_PORT       GPIOB      // LCD复位引脚端口
#define RES_PIN        GPIO_PIN_7 // LCD复位引脚 (PB7)，低电平复位

#define DC_PORT        GPIOB      // 数据/命令选择引脚端口
#define DC_PIN         GPIO_PIN_9 // 数据/命令选择引脚 (PB9)，高电平数据，低电平命令

#define CS_PORT        GPIOB      // 片选引脚端口
#define CS_PIN         GPIO_PIN_8 // 片选引脚 (PB8)，低电平选中

#define BL_PORT        GPIOB      // 背光PWM引脚端口 (TIM3_CH3)
#define BL_PIN         GPIO_PIN_0 // 背光PWM引脚 (PB0)，由TIM3_CH3输出PWM控制亮度

// 引脚操作宏
#define LCD_RES_Clr()   HAL_GPIO_WritePin(RES_PORT, RES_PIN, GPIO_PIN_RESET)
#define LCD_RES_Set()   HAL_GPIO_WritePin(RES_PORT, RES_PIN, GPIO_PIN_SET)

#define LCD_DC_Clr()    HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET)
#define LCD_DC_Set()    HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET)

#define LCD_CS_Clr()    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET)
#define LCD_CS_Set()    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET)

/******************************************************************************
  函数说明：LCD GPIO初始化
******************************************************************************/
void LCD_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = RES_PIN | CS_PIN | DC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, RES_PIN | CS_PIN | DC_PIN, GPIO_PIN_SET);
}

/******************************************************************************
  函数说明：写指令
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
    LCD_DC_Clr();  // 命令模式
    LCD_CS_Clr();
    HAL_SPI_Transmit(&hspi1, &dat, 1, 1);
    LCD_CS_Set();
}

/******************************************************************************
  函数说明：写8位数据
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
    LCD_DC_Set();  // 数据模式
    LCD_CS_Clr();
    HAL_SPI_Transmit(&hspi1, &dat, 1, 1);
    LCD_CS_Set();
}

/******************************************************************************
  函数说明：写16位数据
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
    uint8_t temp[2];
    LCD_DC_Set();  // 数据模式
    LCD_CS_Clr();
    temp[0] = (dat >> 8) & 0xFF;
    temp[1] = dat & 0xFF;
    HAL_SPI_Transmit(&hspi1, temp, 2, 1);
    LCD_CS_Set();
}

/******************************************************************************
  函数说明：设置显示区域
******************************************************************************/
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_WR_REG(0x2A);  // 列地址设置
    LCD_WR_DATA(x1);
    LCD_WR_DATA(x2);

    LCD_WR_REG(0x2B);  // 行地址设置
    LCD_WR_DATA(y1);
    LCD_WR_DATA(y2);

    LCD_WR_REG(0x2C);  // 开始写入GRAM
}

/******************************************************************************
  函数说明：LCD初始化
******************************************************************************/
void LCD_Init(void)
{
    LCD_GPIO_Init();

    LCD_CS_Clr();  // chip select

    // 复位
    LCD_RES_Clr();
    delay_ms(100);
    LCD_RES_Set();
    delay_ms(100);

    // 发送初始化序列
    LCD_WR_REG(0x11);
    delay_ms(120);

    LCD_WR_REG(0x36);  // MADCTL
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0x3A);  // COLMOD: RGB565
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x35);

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x19);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x12);

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x0F);

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xD0);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x2B);
    LCD_WR_DATA8(0x3F);
    LCD_WR_DATA8(0x54);
    LCD_WR_DATA8(0x4C);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x0B);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x23);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0xD0);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x3F);
    LCD_WR_DATA8(0x44);
    LCD_WR_DATA8(0x51);
    LCD_WR_DATA8(0x2F);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x20);
    LCD_WR_DATA8(0x23);

    // 开启显示
    LCD_WR_REG(0x21);
    LCD_WR_REG(0x29);

    delay_ms(100);

    // 清屏
    LCD_Fill(0, 0, LCD_W - 1, LCD_H - 1, BLACK);
}

/******************************************************************************
  函数说明：在指定区域填充颜色 (LVGL接口)
******************************************************************************/
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t i, j;

    LCD_Address_Set(x1, y1, x2, y2);

    for (i = y1; i <= y2; i++)
    {
        for (j = x1; j <= x2; j++)
        {
            LCD_WR_DATA(color);
        }
    }
}

/******************************************************************************
  函数说明：在指定位置画点 (LVGL接口)
******************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Address_Set(x, y, x, y);
    LCD_WR_DATA(color);
}

/******************************************************************************
  函数说明：设置背光亮度 (PWM控制, 5-100)
******************************************************************************/
void LCD_Set_Light(uint8_t brightness)
{
    if (brightness >= 5 && brightness <= 100)
    {
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, brightness * 300 / 100);
    }
}

/******************************************************************************
  函数说明：开启背光
******************************************************************************/
void LCD_Open_Light(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

/******************************************************************************
  函数说明：关闭背光
******************************************************************************/
void LCD_Close_Light(void)
{
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
}
