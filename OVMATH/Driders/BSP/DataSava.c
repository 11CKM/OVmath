#include "DataSava.h"
#include "string.h"
#include "delay.h"

/******************************************
EEPROM Data description:
[0x00]:0x55 for check
[0x01]:0xAA for check

[0x10]:user wrist setting, HWInterface.IMU.wrist_is_enabled
[0x11]:user ui_APPSy_EN setting

[0x20]:Last Save Day(0-31)
[0x21]:Day Steps

*******************************************/


void EEPROM_Init(void)
{
	BL24C02_Init();
}

// to check the Data is right and the EEPROM is working
/**
 * @brief 检查EEPROM是否正常工作
 *
 * 该函数通过读取和写入特定模式(0x55 0xAA)来验证EEPROM的基本功能。
 * 首先尝试读取前两个字节，如果匹配预期值则返回成功；
 * 如果不匹配，则写入测试模式并再次读取验证。
 *
 * @return uint8_t 返回检查结果
 *   @retval 0 检查成功，EEPROM工作正常
 *   @retval 1 检查失败，EEPROM可能存在故障
 *
 * @note 函数内部包含多个延时操作(delay_ms)以确保EEPROM读写时序正确
 */
uint8_t EEPROM_Check(void)
{
    uint8_t check_buff[2];
    delay_ms(10);
	BL24C02_Read(0,2,check_buff);
	if(check_buff[0] == 0x55 && check_buff[1] == 0xAA)
	{
		return 0;//check OK
	}
	else
	{
		check_buff[0] = 0x55;
		check_buff[1] = 0xAA;
		delay_ms(10);
		BL24C02_Write(0,2,check_buff);
		memset(check_buff,0,2);
		delay_ms(10);
		BL24C02_Read(0,2,check_buff);
		if(check_buff[0] == 0x55 && check_buff[1] == 0xAA)
			return 0;//check ok
	}
	return 1;//check erro
}

// to Save the settings
/**
 * @brief 保存设置数据到EEPROM
 *
 * @param buf 要保存的数据缓冲区指针
 * @param addr EEPROM起始地址(必须大于1)
 * @param lenth 要保存的数据长度
 * @return uint8_t 执行结果：0-成功，1-失败
 * @note 执行前会自动检查EEPROM状态，并添加10ms延时确保操作稳定
 */
uint8_t SettingSave(uint8_t *buf, uint8_t addr, uint8_t lenth)
{
    if (addr > 1 && !EEPROM_Check())
    {
		delay_ms(10);
		BL24C02_Write(addr,lenth,buf);
		return 0;
	}
	return 1;
}

// to Get the settings
/**
 * @brief 从EEPROM中读取设置数据
 *
 * @param buf 存储读取数据的缓冲区指针
 * @param addr EEPROM中的起始地址
 * @param lenth 要读取的数据长度
 * @return uint8_t 读取状态：0表示成功，1表示失败
 *
 * @note 当地址大于1时，会先检查EEPROM状态并延迟10ms
 *       如果EEPROM检查失败或地址无效，则返回失败状态
 */
uint8_t SettingGet(uint8_t *buf, uint8_t addr, uint8_t lenth)
{
    if (addr > 1 && !EEPROM_Check())
    {
		delay_ms(10);
		BL24C02_Read(addr,lenth,buf);
		return 0;
	}
	return 1;
}
