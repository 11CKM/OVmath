#include "primer.h"
#include "adc.h"


void POWER_EN()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
}

void POWER_END()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
}

uint8_t ChargeCheck()
{
    return HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);
}

float  PowerSize()
{
    uint16_t bat ;
    float BordAdd;
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,5);
    bat = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    BordAdd = bat * 2 * 3.3 /4096;
    return BordAdd;
}


float  PowerSize_8Times()
{
    float BordAdd8 = 0;
    for (int i = 0; i < 8; i++)
    {
        BordAdd8+=PowerSize();
        HAL_Delay(1);
    }
    BordAdd8 = BordAdd8/8;
    return BordAdd8;
}

uint8_t PowerCalculate()
{
	uint8_t power = 0;
	float voltage;
    voltage = PowerSize_8Times();
    if ( ChargeCheck())
    {
        voltage -= 0.128f;
    }
	if((voltage >= 4.2f))
	{power = 100;}
	else if(voltage >= 4.06f && voltage <4.2f)
	{power = 90;}
	else if(voltage >= 3.98f && voltage <4.06f)
	{power = 80;}
	else if(voltage >= 3.92f && voltage <3.98f)
	{power = 70;}
	else if(voltage >= 3.87f && voltage <3.92f)
	{power = 60;}
	else if(voltage >= 3.82f && voltage <3.87f)
	{power = 50;}
	else if(voltage >= 3.79f && voltage <3.82f)
	{power = 40;}
	else if(voltage >= 3.77f && voltage <3.79f)
	{power = 30;}
	else if(voltage >= 3.74f && voltage <3.77f)
	{power = 20;}
	else if(voltage >= 3.68f && voltage <3.74f)
	{power = 10;}
	else if(voltage >= 3.45f && voltage <3.68f)
	{power = 5;}
	return power;    
}

void POWER_INIT()
{
	POWER_EN();
}
