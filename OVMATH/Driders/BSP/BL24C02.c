#include "BL24C02.h"

#define BL_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()

IIC_Pin BL_bus = 
{
	.II2C_SDA_PORT = GPIOA,
	.II2C_SCL_PORT = GPIOA,
	.IIC_PIN_SDA  = GPIO_PIN_11,
	.IIC_PIN_SCL  = GPIO_PIN_12,
};

/**
 * @brief 向BL24C02 EEPROM写入数据
 *
 * @param addr 写入起始地址
 * @param length 要写入的数据长度
 * @param buff 包含待写入数据的缓冲区
 */
void BL24C02_Write(uint8_t addr, uint8_t length, uint8_t buff[])
{
    IIC_Write_Multi_Byte(&BL_bus, BL_ADDRESS, addr, length, buff);
}

/**
 * @brief 从BL24C02 EEPROM读取数据
 *
 * @param addr 要读取的起始地址
 * @param length 要读取的数据长度
 * @param buff 存储读取数据的缓冲区
 */
void BL24C02_Read(uint8_t addr, uint8_t length, uint8_t buff[])
{
    IIC_Read_Multi_Byte(&BL_bus, BL_ADDRESS, addr, length, buff);
}

void BL24C02_Init(void)
{
	BL_CLK_ENABLE;
	IIC_Init(&BL_bus);
}
