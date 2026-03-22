#include "AHT21.h"

#define AHT_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE()
static IIC_Pin AHT_bus = {
	.II2C_SDA_PORT = GPIOB,
	.II2C_SCL_PORT = GPIOB,
	.IIC_PIN_SDA  = GPIO_PIN_13,
	.IIC_PIN_SCL  = GPIO_PIN_14,
};

uint8_t AHT_Read_Status(void)
{
	uint8_t Byte_first;
	IIC_Start(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0x71);
	IIC_Wait_Ack(&AHT_bus);
	Byte_first = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Nack(&AHT_bus);
	IIC_Stop(&AHT_bus);
	return Byte_first;
}

uint8_t AHT_Read_Cal_Enable(void)  //check cal enable bit 
{
	uint8_t val = 0;//ret = 0,
 
  val = AHT_Read_Status();
  if((val & 0x68)==0x08)  //check NOR mode 
		return 1;
  else  
		return 0;
}

void AHT_Reset(void)//AHT21 send 0xBA reset call
{
	IIC_Start(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0x70);
	IIC_Wait_Ack(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0xBA);
	IIC_Wait_Ack(&AHT_bus);
	IIC_Stop(&AHT_bus);
}

uint8_t AHT_Init(void)
{
	AHT_CLK_ENABLE;
	IIC_Init(&AHT_bus);

	delay_ms(40);

	if(AHT_Read_Status()&&0x08!=0x08)
	{
		IIC_Start(&AHT_bus);
		IIC_Send_Byte(&AHT_bus,0x70);
		IIC_Wait_Ack(&AHT_bus);
		IIC_Send_Byte(&AHT_bus,0xBE);
		IIC_Wait_Ack(&AHT_bus);
		IIC_Send_Byte(&AHT_bus,0x08);
		IIC_Wait_Ack(&AHT_bus);
		IIC_Send_Byte(&AHT_bus,0x00);
		IIC_Wait_Ack(&AHT_bus);
		IIC_Stop(&AHT_bus);
		delay_ms(10);
	}
	//AHT_Reset();

	return 0;
}	
 
uint8_t AHT_Read(float *humi, float *temp)
{
	uint8_t cnt=5;
	uint8_t  Byte_1th=0;
	uint8_t  Byte_2th=0;
	uint8_t  Byte_3th=0;
	uint8_t  Byte_4th=0;
	uint8_t  Byte_5th=0;
	uint8_t  Byte_6th=0;
	uint32_t RetuData = 0;

	IIC_Start(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0x70);
	IIC_Wait_Ack(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0xAC);
	IIC_Wait_Ack(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0x33);
	IIC_Wait_Ack(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0x00);
	IIC_Wait_Ack(&AHT_bus);
	IIC_Stop(&AHT_bus);

	delay_ms(80);
	while(AHT_Read_Status()&0x80==0x80 && cnt)
	{
		delay_ms(5);
		cnt--;
		AHT_Read_Status();
	}
	if(!cnt)
	{return 1;}

	IIC_Start(&AHT_bus);
	IIC_Send_Byte(&AHT_bus,0x71);
	IIC_Wait_Ack(&AHT_bus);
	Byte_1th = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Ack(&AHT_bus);
	Byte_2th = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Ack(&AHT_bus);
	Byte_3th = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Ack(&AHT_bus);
	Byte_4th = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Ack(&AHT_bus);
	Byte_5th = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Ack(&AHT_bus);
	Byte_6th = IIC_Receive_Byte(&AHT_bus);
	IIC_Send_Nack(&AHT_bus);
	IIC_Stop(&AHT_bus);

	RetuData = (RetuData|Byte_2th)<<8;
	RetuData = (RetuData|Byte_3th)<<8;
	RetuData = (RetuData|Byte_4th);
	RetuData =RetuData >>4;
	*humi = (RetuData * 1000 >> 20);
	*humi /= 10;

	RetuData = 0;
	RetuData = (RetuData|(Byte_4th&0x0f))<<8;
	RetuData = (RetuData|Byte_5th)<<8;
	RetuData = (RetuData|Byte_6th);
	RetuData = RetuData&0xfffff;
	*temp = ((RetuData * 2000 >> 20)- 500);
	*temp /= 10;

	return 0;
}


