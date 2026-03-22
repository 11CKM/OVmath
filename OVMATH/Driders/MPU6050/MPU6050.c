#include "MPU6050.h"

#define MPU_INT_PORT GPIOB
#define MPU_INT_PIN  GPIO_PIN_12

#define CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE();

static IIC_Pin MPU_bus = {
	.II2C_SDA_PORT = GPIOB,
	.II2C_SCL_PORT = GPIOB,
	.IIC_PIN_SDA  = GPIO_PIN_13,
	.IIC_PIN_SCL  = GPIO_PIN_14,
};


/**************************************************************************/
/*!
    @brief  initialize iic port connect with MPU6050

    @param  NULL
*/
/**************************************************************************/
void MPU_INT_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}


/**************************************************************************/
/*!
    @brief  initialize motion function of MPU6050

    @param  NULL
*/
/**************************************************************************/
void MPU_Motion_Init(void)
{
    MPU_Write_Byte(MPU_MOTION_DET_REG, 0x01);    //set the acceleration threshold is (LSB*2)mg
    MPU_Write_Byte(MPU_MOTION_DUR_REG, 0x01);    //Acceleration detection time is ()ms
    MPU_Write_Byte(MPU_INTBP_CFG_REG, 0X90);     //INT Pin active low level, reset until 50us
    MPU_Write_Byte(MPU_INT_EN_REG, 0x40);        //enable INT
}


/**************************************************************************/
/*!
    @brief  initialize the IIC bus

    @param  NULL
*/
/**************************************************************************/
void MPU_Bus_Init(void)
{
	CLK_ENABLE;
	IIC_Init(&MPU_bus);
}


/**************************************************************************/
/*!
    @brief  init the MPU6050

    @param  NULL

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Init(void)
{
	uint8_t res;

	MPU_Bus_Init();

	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X80);	//复位MPU6050
  delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X00);	//唤醒MPU6050
	MPU_Set_Gyro_Fsr(3);										//G传感器, 2000dps
	MPU_Set_Accel_Fsr(2);										//A传感器, 8g
	MPU_Set_Rate(50);												//采样率50Hz
	MPU_Write_Byte(MPU_INT_EN_REG, 0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG, 0X00);	//IIC主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG, 0X00);	//dis FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG, 0X80);	//INT active low

	res = MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res == MPU_ADDR)//ID
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X28);	//SET the internal 8MHz,sleep=0,cycle=1,TEMP_DIS=1//low power modes
		MPU_Write_Byte(MPU_PWR_MGMT2_REG, 0X87);	//enable accelerometer,disable gyroscope,set the wake up frequency=20Hz
		MPU_Set_Rate(50);												//采样率50Hz
 	}else return 1;

	MPU_Motion_Init();
	MPU_INT_Pin_Init();

	return 0;
}

void MPU_Sleep(void)
{
	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x48);//sleep=1,cycle=0,temp_dis=1,internal 8MHz
}

void MPU_Wakeup(void)
{
	//low power modes
	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x28);//sleep=0,cycle=1,temp_dis=1,internal 8MHz
}

uint8_t MPU_Read_Status(void)
{
	return MPU_Read_Byte(MPU_INT_STA_REG);
}


/**************************************************************************/
/*
    @brief  设置MPU6050陀螺仪传感器满量程范围

    @param  fsr:0,+250dps;1,500dps;2,+1000dps;3,+2000dps

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG, fsr<<3);
}


/**************************************************************************/
/*
    @brief  设置MPU6050的数字低通滤波器

    @param  fsr:低通滤波器频率(Hz)

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG, fsr<<3);
}


/**************************************************************************/
/*
    @brief  设置MPU6050的低通滤波器

    @param  lpf: Hz

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data = 0;
	if(lpf >= 188) data = 1;
	else if(lpf >= 98) data = 2;
	else if(lpf >= 42) data = 3;
	else if(lpf >= 20) data = 4;
	else if(lpf >= 10) data = 5;
	else data = 6;
	return MPU_Write_Byte(MPU_CFG_REG, data);
}


/**************************************************************************/
/*
    @brief  设置MPU6050的采样率

    @param  rate: 4~1000 Hz

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate > 1000) rate = 1000;
	if(rate < 4) rate = 4;
	data = 1000 / rate - 1;
	data = MPU_Write_Byte(MPU_SAMPLE_RATE_REG, data);
 	return MPU_Set_LPF(rate / 2);
}

/**************************************************************************/
/*
    @brief  获取MPU6050温度值

    @param  NULL

    @return temperature (short)
*/
/**************************************************************************/
int16_t MPU_Get_Temperature(void)
{
    uint8_t buf[2];
    int16_t raw;
	float temp;
	MPU_Read_Len(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf);
    raw = ((uint16_t)buf[0] << 8) | buf[1];
    temp = 36.53 + ((double)raw) / 340;
    return (int16_t)(temp * 100);
}


/**************************************************************************/
/*
    @brief  获取MPU6050陀螺仪原始值

    @param  NULL

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Get_Gyroscope(int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t buf[6], res;
	res = MPU_Read_Len(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
	if(res == 0)
	{
		*gx = ((uint16_t)buf[0] << 8) | buf[1];
		*gy = ((uint16_t)buf[2] << 8) | buf[3];
		*gz = ((uint16_t)buf[4] << 8) | buf[5];
	}
    return res;
}


/**************************************************************************/
/*
    @brief  获取MPU6050加速度原始值

    @param  NULL

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Get_Accelerometer(int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t buf[6], res;
	res = MPU_Read_Len(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf);
	if(res == 0)
	{
		*ax = ((uint16_t)buf[0] << 8) | buf[1];
		*ay = ((uint16_t)buf[2] << 8) | buf[3];
		*az = ((uint16_t)buf[4] << 8) | buf[5];
	}
    return res;
}

/**************************************************************************/
/*
    @brief  IIC连续写

    @param  addr:器件地址
    @param  reg:寄存器地址
	@param  len:写入长度
	@param  buf:数据区

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	uint8_t i;
  IIC_Start(&MPU_bus);
	IIC_Send_Byte(&MPU_bus, (addr<<1) | 0);
	if(IIC_Wait_Ack(&MPU_bus))
	{
		IIC_Stop(&MPU_bus);
		return 1;
	}
    IIC_Send_Byte(&MPU_bus, reg);
    IIC_Wait_Ack(&MPU_bus);
	for(i = 0; i < len; i++)
	{
		IIC_Send_Byte(&MPU_bus, buf[i]);
		if(IIC_Wait_Ack(&MPU_bus))
		{
			IIC_Stop(&MPU_bus);
			return 1;
		}
	}
    IIC_Stop(&MPU_bus);
	return 0;
}

/**************************************************************************/
/*
    @brief  IIC写单字节

    @param  reg:寄存器地址
	@param  data:数据(uint8_t)

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Write_Byte(uint8_t reg, uint8_t data)
{
    IIC_Start(&MPU_bus);
	IIC_Send_Byte(&MPU_bus, (MPU_ADDR<<1) | 0);
	if(IIC_Wait_Ack(&MPU_bus))
	{
		IIC_Stop(&MPU_bus);
		return 1;
	}
	IIC_Send_Byte(&MPU_bus, reg);
	IIC_Wait_Ack(&MPU_bus);
	IIC_Send_Byte(&MPU_bus, data);
	if(IIC_Wait_Ack(&MPU_bus))
	{
		IIC_Stop(&MPU_bus);
		return 1;
	}
  IIC_Stop(&MPU_bus);
	return 0;
}


/**************************************************************************/
/*
    @brief  IIC读单字节

    @param  reg:寄存器地址

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Read_Byte(uint8_t reg)
{
	uint8_t res;
  IIC_Start(&MPU_bus);
	IIC_Send_Byte(&MPU_bus, (MPU_ADDR<<1) | 0);
	IIC_Wait_Ack(&MPU_bus);
  IIC_Send_Byte(&MPU_bus, reg);
  IIC_Wait_Ack(&MPU_bus);
  IIC_Start(&MPU_bus);
	IIC_Send_Byte(&MPU_bus, (MPU_ADDR<<1) | 1);
  IIC_Wait_Ack(&MPU_bus);
	res = IIC_Receive_Byte(&MPU_bus);
	IIC_Send_Nack(&MPU_bus);
  IIC_Stop(&MPU_bus);
	return res;
}


/**************************************************************************/
/*
    @brief  IIC连续读

    @param  addr:器件地址
    @param  reg:寄存器地址
	@param  len:写入长度
	@param  buf:数据区

    @return 0 if success
*/
/**************************************************************************/
uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
 	IIC_Start(&MPU_bus);
	IIC_Send_Byte(&MPU_bus, (addr<<1) | 0);
	if(IIC_Wait_Ack(&MPU_bus))
	{
		IIC_Stop(&MPU_bus);
		return 1;
	}
    IIC_Send_Byte(&MPU_bus, reg);
    IIC_Wait_Ack(&MPU_bus);
    IIC_Start(&MPU_bus);
		IIC_Send_Byte(&MPU_bus, (addr<<1) | 1);
    IIC_Wait_Ack(&MPU_bus);
		while(len)
		{
			if(len == 1)
			{
				*buf = IIC_Receive_Byte(&MPU_bus);
				IIC_Send_Nack(&MPU_bus);
			}
			else
			{
				*buf = IIC_Receive_Byte(&MPU_bus);
				IIC_Send_Ack(&MPU_bus);
			}
			len--;
			buf++;
		}
    IIC_Stop(&MPU_bus);
		return 0;
}

uint8_t MPU_Write_Multi_Byte(uint8_t addr, uint8_t length, uint8_t buff[])
{
	if(IIC_Write_Multi_Byte(&MPU_bus, MPU_ADDR, addr, length, buff))
	{
		return 1;
	}
	return 0;
}

uint8_t MPU_Read_Multi_Byte(uint8_t addr, uint8_t length, uint8_t buff[])
{
	if(IIC_Read_Multi_Byte(&MPU_bus, MPU_ADDR, addr, length, buff))
	{
		return 1;
	}
	return 0;
}


/**************************************************************************/
/*
    @brief  get the roll and pitch

    @param  roll:roll(float)
    @param  pitch:pitch(float)

    @return NULL
*/
/**************************************************************************/
void MPU_Get_Angles(float *roll, float *pitch)
{
	int16_t ax, ay, az;
	MPU_Get_Accelerometer(&ax, &ay, &az);
	*pitch = -atanf(ax / sqrtf(ay*ay + az*az));
	*roll = atanf((float)ay / (float)az);
}


/**************************************************************************/
/*
    @brief  check the MPU6050 is horizontal or not

    @param  NULL

    @return 1 if is horizontal
*/
/**************************************************************************/
uint8_t MPU_isHorizontal(void)
{
	float roll, pitch;
	MPU_Get_Angles(&roll, &pitch);
	if(roll <= 0.50 && roll >= -0.50 && pitch <= 0.50 && pitch >= -0.50)
	{return 1;}
	return 0;
}
