#ifndef __BL24C02_H
#define __BL24C02_H
//这个文件是 BL24C02 EEPROM 芯片的驱动程序，用于读写外部非易失性存储器。
#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "delay.h"

#define BL_ADDRESS	0x50

void BL24C02_Write(uint8_t addr,uint8_t length,uint8_t buff[]);
void BL24C02_Read(uint8_t addr, uint8_t length, uint8_t buff[]);
void BL24C02_Init(void);

#endif
