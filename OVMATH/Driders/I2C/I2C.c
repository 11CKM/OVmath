#include "I2C.h"
#include "delay.h"

/**
  * @brief 使能GPIO时钟
  * @param GPIOx: GPIO端口
  * @retval None
  */
void IIC_Enable_Clock(GPIO_TypeDef* GPIOx)
{
    if(GPIOx == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if(GPIOx == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if(GPIOx == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if(GPIOx == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if(GPIOx == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
    else if(GPIOx == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
}

/**
  * @brief I2C总线初始化
  * @param bus: I2C总线结构体指针
  * @retval None
  */
void IIC_Init(IIC_Pin *bus)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // =====================================
    // 1. 使能GPIO时钟
    // =====================================
    IIC_Enable_Clock(bus->II2C_SDA_PORT);
    IIC_Enable_Clock(bus->II2C_SCL_PORT);
    
    // =====================================
    // 2. 配置SDA引脚
    // =====================================
    GPIO_InitStruct.Pin = bus->IIC_PIN_SDA;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;    // 开漏输出
    GPIO_InitStruct.Pull = GPIO_PULLUP;            // 上拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  // 高速
    HAL_GPIO_Init(bus->II2C_SDA_PORT, &GPIO_InitStruct);
    
    // =====================================
    // 3. 配置SCL引脚
    // =====================================
    GPIO_InitStruct.Pin = bus->IIC_PIN_SCL;
    HAL_GPIO_Init(bus->II2C_SCL_PORT, &GPIO_InitStruct);
    
    // =====================================
    // 4. 设置总线初始状态
    // =====================================
    SDA_Output(bus, 1);  
    SCL_Output(bus, 1);  
    
    // =====================================
    // 5. 短暂延时
    // =====================================
    delay_us(10);
}
/**
  * @brief SCL线输出一个位（修正版）
  * @param val: 0=低电平, 非0=高电平
  * @retval None
  */
void SCL_Output(IIC_Pin *bus, uint8_t val)
{
    if(val) {
        // 设置高电平：使用=，不是|=
        bus->II2C_SCL_PORT->BSRR = bus->IIC_PIN_SCL;
    } else {
        // 设置低电平
        bus->II2C_SCL_PORT->BSRR = (uint32_t)bus->IIC_PIN_SCL << 16U;
    }
}

/**
  * @brief SDA线输出一个位（修正版）
  * @param val: 0=低电平, 非0=高电平
  * @retval None
  */
void SDA_Output(IIC_Pin *bus, uint8_t val)
{
    if(val) {
        // 设置高电平：使用=，不是|=
        bus->II2C_SDA_PORT->BSRR = bus->IIC_PIN_SDA;
    } else {
        // 设置低电平
        bus->II2C_SDA_PORT->BSRR = (uint32_t)bus->IIC_PIN_SDA << 16U;
    }
}

/**
  * @brief 读取SDA引脚状态（建议改名）
  * @param bus: I2C总线结构体指针
  * @retval 0=低电平, 1=高电平
  */
uint8_t SDA_Input(IIC_Pin *bus)
{
    return (HAL_GPIO_ReadPin(bus->II2C_SDA_PORT, bus->IIC_PIN_SDA) == GPIO_PIN_SET) ? 1 : 0;
}


// ==================== 基础时序函数 ====================

/**
  * @brief IIC起始信号
  */
void IIC_Start(IIC_Pin *bus)
{
    // 1. 确保总线空闲
    SDA_Output(bus, 1);
    delay_us(5);
    SCL_Output(bus, 1);
    delay_us(5);
    
    // 2. 产生起始条件（SCL高时SDA下降沿）
    SDA_Output(bus, 0);
    delay_us(5);
    
    // 3. 拉低SCL，准备数据传输
    SCL_Output(bus, 0);
    delay_us(2);
}

/**
  * @brief IIC停止信号
  */
void IIC_Stop(IIC_Pin *bus)
{
    // 1. 确保SCL和SDA为低
    SCL_Output(bus, 0);
    delay_us(2);
    SDA_Output(bus, 0);
    delay_us(2);
    
    // 2. 先拉高SCL
    SCL_Output(bus, 1);
    delay_us(5);
    
    // 3. 产生停止条件（SCL高时SDA上升沿）
    SDA_Output(bus, 1);
    delay_us(5);
}

/**
  * @brief IIC等待ACK
  * @retval 0:收到ACK, 1:收到NACK或超时
  */
uint8_t IIC_Wait_Ack(IIC_Pin *bus)
{
    uint16_t timeout = 1000;
    
    // 1. 主机释放SDA
    SDA_Output(bus, 1);
    delay_us(2);
    
    // 2. 拉高SCL
    SCL_Output(bus, 1);
    delay_us(5);  // 等待从机设置SDA
    
    // 3. 读取ACK
    while (SDA_Input(bus) == 1) {  // 等待SDA被拉低
        delay_us(1);
        timeout--;
        if (timeout == 0) {
            IIC_Stop(bus);
            return 1;
        }
    }
    // 4. 拉低SCL结束ACK周期
    SCL_Output(bus, 0);
    delay_us(2);
    return 0;
}

/**
  * @brief IIC发送ACK
  */
void IIC_Send_Ack(IIC_Pin *bus)
{
    SCL_Output(bus, 0);
    delay_us(2);
    SDA_Output(bus, 0);  // ACK=低电平
    delay_us(2);
    SCL_Output(bus, 1);
    delay_us(5);
    SCL_Output(bus, 0);
    delay_us(2);
    SDA_Output(bus,1);
    delay_us(2);
}

/**
  * @brief IIC发送NACK
  */
void IIC_Send_Nack(IIC_Pin *bus)
{
    SCL_Output(bus, 0);
    delay_us(2);
    SDA_Output(bus, 1);  // NACK=高电平
    delay_us(2);
    SCL_Output(bus, 1);
    delay_us(5);
    SCL_Output(bus, 0);
    delay_us(2);
}

/**
  * @brief IIC发送一个字节
  */
uint8_t IIC_Send_Byte(IIC_Pin *bus, uint8_t data)
{
    uint8_t i;
    
    for (i = 0; i < 8; i++) {
        // 先拉低SCL
        SCL_Output(bus, 0);
        delay_us(2);
        
        // 设置数据位（MSB first）
        if (data & 0x80) {
            SDA_Output(bus, 1);
        } else {
            SDA_Output(bus, 0);
        }
        data <<= 1;  // 左移一位
        
        // 拉高SCL，数据被采样
        SCL_Output(bus, 1);
        delay_us(5);
        
        // 拉低SCL，准备下一位
        SCL_Output(bus, 0);
        delay_us(2);
    }
    
    // 等待ACK
    return IIC_Wait_Ack(bus);
}

/**
  * @brief IIC接收一个字节
  */
uint8_t IIC_Receive_Byte(IIC_Pin *bus)
{
    uint8_t i;
    uint8_t received_data = 0;
    
    SDA_Output(bus, 1);  // 释放SDA
    SCL_Output(bus, 0);
    delay_us(2);
    
    for (i = 0; i < 8; i++) {
        received_data <<= 1;  // 先左移
        
        SCL_Output(bus, 1);
        delay_us(5);
        
        if (SDA_Input(bus)) {
            received_data |= 0x01;  // 设置最低位
        }
        
        SCL_Output(bus, 0);
        delay_us(2);
    }
    
    return received_data;
}


// ==================== 高级读写函数 ====================

uint8_t IIC_Write_One_Byte(IIC_Pin *bus, uint8_t dev_addr, uint8_t reg, uint8_t data)
{
    IIC_Start(bus);
    
    // 发送设备地址（写模式）
    if (IIC_Send_Byte(bus, dev_addr << 1)) {
        IIC_Stop(bus);
        return 1;  // 地址无响应
    }
    
    // 发送寄存器地址
    if (IIC_Send_Byte(bus, reg)) {
        IIC_Stop(bus);
        return 2;  // 寄存器地址无响应
    }
    
    // 发送数据
    if (IIC_Send_Byte(bus, data)) {
        IIC_Stop(bus);
        return 3;  // 数据无响应
    }
    
    IIC_Stop(bus);
    delay_us(10);  // 等待写操作完成
    return 0;  // 成功
}

/**
  * @brief IIC写入多个字节
  * @param bus: I2C总线结构体指针
  * @param daddr: 设备地址（7位）
  * @param reg: 起始寄存器地址
  * @param length: 要写入的字节数
  * @param buff: 数据缓冲区
  * @retval 0:成功, 1:设备无响应
  */
uint8_t IIC_Write_Multi_Byte(IIC_Pin *bus, uint8_t daddr, uint8_t reg, 
                            uint8_t length, uint8_t buff[])
{
    unsigned char i;
    
    // 1. 启动I2C通信
    IIC_Start(bus);
    
    // 2. 发送设备地址（写模式）
    if (IIC_Send_Byte(bus, daddr << 1)) {
        IIC_Stop(bus);
        return 1;  // 设备无响应
    }
    
    // 3. 发送寄存器地址
    IIC_Send_Byte(bus, reg);
    IIC_Wait_Ack(bus);
    
    // 4. 循环发送多个数据字节
    for (i = 0; i < length; i++) {
        IIC_Send_Byte(bus, buff[i]);  // 发送数据字节
        IIC_Wait_Ack(bus);            // 等待ACK
    }
    
    // 5. 停止传输
    IIC_Stop(bus);
    delay_us(1);  // 等待写操作完成
    
    return 0;  // 成功
}

uint8_t IIC_Read_One_Byte(IIC_Pin *bus, uint8_t dev_addr, uint8_t reg)
{
    uint8_t data = 0;
    
    // 1. 发送寄存器地址（写模式）
    IIC_Start(bus);
    IIC_Send_Byte(bus, dev_addr << 1);      // 设备地址+写
    IIC_Send_Byte(bus, reg);               // 寄存器地址
    
    // 2. 重新起始，改为读模式
    IIC_Start(bus);
    IIC_Send_Byte(bus, (dev_addr << 1) | 0x01);  // 设备地址+读
    
    // 3. 读取数据
    data = IIC_Receive_Byte(bus);
    
    // 4. 发送NACK，停止
    IIC_Send_Nack(bus);
    IIC_Stop(bus);
    
    return data;
}

/**
  * @brief IIC读取多个字节
  * @param bus: I2C总线结构体指针
  * @param daddr: 设备地址（7位）
  * @param reg: 起始寄存器地址
  * @param length: 要读取的字节数
  * @param buff: 存储数据的缓冲区
  * @retval 0:成功, 1:设备无响应
  */
uint8_t IIC_Read_Multi_Byte(IIC_Pin *bus, uint8_t daddr, uint8_t reg, 
                           uint8_t length, uint8_t buff[])
{
    unsigned char i;
    
    // 1. 启动I2C通信
    IIC_Start(bus);
    
    // 2. 发送设备地址（写模式）
    if (IIC_Send_Byte(bus, daddr << 1)) {
        IIC_Stop(bus);
        return 1;  // 设备无响应
    }
    
    // 3. 发送寄存器地址
    IIC_Send_Byte(bus, reg);
    IIC_Wait_Ack(bus);
    
    // 4. 重新起始，切换到读模式
    IIC_Start(bus);
    IIC_Send_Byte(bus, (daddr << 1) | 0x01);  // 地址+读模式
    IIC_Wait_Ack(bus);
    
    // 5. 循环读取多个字节
    for (i = 0; i < length; i++) {
        buff[i] = IIC_Receive_Byte(bus);  // 接收一个字节
        
        // 发送ACK或NACK
        if (i < length - 1) {
            IIC_Send_Ack(bus);      // 前n-1个字节：发送ACK（继续）
        }
        // 最后一个字节暂时不处理
    }
    
    // 6. 发送NACK（最后一个字节）
    IIC_Send_Nack(bus);
    
    // 7. 停止传输
    IIC_Stop(bus);
    
    return 0;  // 成功
}

