#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"
#include "stm32f4xx_hal.h"

// LCD分辨率定义
#define LCD_W 240
#define LCD_H 280

// 颜色定义 (RGB565格式)
#define WHITE          0xFFFF
#define BLACK          0x0000
#define BLUE           0x001F
#define BRED           0xF81F
#define GRED           0xFFE0
#define GBLUE          0x07FF
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define BROWN          0xBC40
#define BRRED          0xFC07
#define GRAY           0x8430
#define DARKBLUE       0x01CF
#define LIGHTBLUE      0x7D7C
#define GRAYBLUE       0x5458
#define LIGHTGREEN     0x841F
#define LGRAY          0xC618
#define LGRAYBLUE      0xA651
#define LBBLUE         0x2B12

// LCD引脚定义（供LVGL使用）
#define RES_PORT       GPIOB       // LCD复位引脚端口
#define RES_PIN        GPIO_PIN_7  // LCD复位引脚 (PB7)，低电平复位

#define DC_PORT        GPIOB       // 数据/命令选择引脚端口
#define DC_PIN         GPIO_PIN_9  // 数据/命令选择引脚 (PB9)，高电平数据，低电平命令

#define CS_PORT        GPIOB       // 片选引脚端口
#define CS_PIN         GPIO_PIN_8  // 片选引脚 (PB8)，低电平选中

// 引脚操作宏定义（供LVGL flush回调使用）
#define LCD_RES_Clr()   HAL_GPIO_WritePin(RES_PORT, RES_PIN, GPIO_PIN_RESET)
#define LCD_RES_Set()   HAL_GPIO_WritePin(RES_PORT, RES_PIN, GPIO_PIN_SET)

#define LCD_DC_Clr()    HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET)
#define LCD_DC_Set()    HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET)

#define LCD_CS_Clr()    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET)
#define LCD_CS_Set()    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET)

// LVGL接口要求的显示驱动函数
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);

// 硬件初始化函数
void LCD_Init(void);
void LCD_GPIO_Init(void);
void LCD_Set_Light(uint8_t brightness);  // 5-100, PWM控制
void LCD_Open_Light(void);
void LCD_Close_Light(void);

// 底层驱动函数（供LVGL flush回调使用）
void LCD_WR_REG(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif
