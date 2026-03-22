#ifndef _I2C_H_
#define _I2C_H_

#include "stm32f4xx_hal.h"
#include "delay.h"

typedef struct
{
    GPIO_TypeDef * II2C_SDA_PORT;
    GPIO_TypeDef * II2C_SCL_PORT;
    uint16_t IIC_PIN_SDA;
    uint16_t IIC_PIN_SCL;
} IIC_Pin;

void IIC_Enable_Clock(GPIO_TypeDef* GPIOx);
void IIC_Init(IIC_Pin *bus);
void SCL_Output(IIC_Pin *bus, uint8_t val);
void SDA_Output(IIC_Pin *bus, uint8_t val);
uint8_t SDA_Input(IIC_Pin *bus);

// 基础时序函数
void IIC_Start(IIC_Pin *bus);
void IIC_Stop(IIC_Pin *bus);
uint8_t IIC_Wait_Ack(IIC_Pin *bus);
void IIC_Send_Ack(IIC_Pin *bus);
void IIC_Send_Nack(IIC_Pin *bus);
uint8_t IIC_Send_Byte(IIC_Pin *bus, uint8_t data);
uint8_t IIC_Receive_Byte(IIC_Pin *bus);

// 高级读写函数
uint8_t IIC_Write_One_Byte(IIC_Pin *bus, uint8_t dev_addr, uint8_t reg, uint8_t data);
uint8_t IIC_Write_Multi_Byte(IIC_Pin *bus, uint8_t dev_addr, uint8_t reg, 
                            uint8_t length, uint8_t buff[]);
uint8_t IIC_Read_One_Byte(IIC_Pin *bus, uint8_t dev_addr, uint8_t reg);
uint8_t IIC_Read_Multi_Byte(IIC_Pin *bus, uint8_t dev_addr, uint8_t reg,
                           uint8_t length, uint8_t buff[]);

#endif
