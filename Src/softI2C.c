
#include "softI2C.h"

/* I2C param */
#define WaitCycle (48-3)
#define WaitTime 1      //Real Time = WaitTime * WaitCyale
#define ACK_TimeOut 220

// 软件 I2C 的时许延迟
void soft_i2c_Delay(uint16_t xus)
{
    volatile  uint32_t xx;
    volatile uint16_t aa = xus;
    while(aa--)
    {
//        __ASM("nop");
        xx = WaitCycle;
        while(xx--);
    }
}

void soft_i2c_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = ESDA_Pin | ESCL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init( ESCL_GPIO_Port, &GPIO_InitStruct );
    GPIO_InitStruct.Pin = EWP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init( EWP_GPIO_Port, &GPIO_InitStruct );
    soft_i2c_Stop();
}

void soft_i2c_Start()
{
    SCL_HIGH();
    SDA_HIGH();
    soft_i2c_Delay(WaitTime);
    SDA_LOW();
    soft_i2c_Delay(WaitTime);
    SCL_LOW();
    soft_i2c_Delay(WaitTime);
}

void soft_i2c_Stop()
{
    SCL_LOW();
    SDA_LOW();
    soft_i2c_Delay(WaitTime);
    SCL_HIGH();
    soft_i2c_Delay(WaitTime);
    SDA_HIGH();
    soft_i2c_Delay(WaitTime);
}


uint8_t soft_i2c_Wait_ACK()
{
    uint8_t ret;
    volatile uint16_t xCNT;
    SDA_HIGH();
    soft_i2c_Delay(WaitTime);
    SCL_HIGH();
    soft_i2c_Delay(WaitTime);
    ret = 0;
    while(READ_SDA() != 0)
    {
        xCNT++;
        if(xCNT > ACK_TimeOut)
        {
            SCL_LOW();
            ret = 1;
            break;
        }
    }
    SCL_LOW();
    soft_i2c_Delay(WaitTime);
    return ret;
}

void soft_i2c_Send_ACK()
{
    SDA_LOW();
    soft_i2c_Delay(WaitTime);
    SCL_HIGH();
    soft_i2c_Delay(WaitTime);
    SCL_LOW();
    soft_i2c_Delay(WaitTime);
    SDA_HIGH();
    soft_i2c_Delay(WaitTime);
}

void soft_i2c_Send_NACK()
{
    SCL_LOW();
    soft_i2c_Delay(WaitTime);
    SDA_HIGH();
    soft_i2c_Delay(WaitTime);
    SCL_HIGH();
    soft_i2c_Delay(WaitTime);
    SCL_LOW();
    soft_i2c_Delay(WaitTime);
}

void soft_i2c_Write_Byte(uint8_t Val)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if((Val & 0x80) > 0)
        {
            SDA_HIGH();
        }
        else
        {
            SDA_LOW();
        }
        soft_i2c_Delay(WaitTime);
        SCL_HIGH();
        soft_i2c_Delay(WaitTime);
        SCL_LOW();
        soft_i2c_Delay(WaitTime);
        Val <<= 1;
    }
}

uint8_t soft_i2c_Read_Byte()
{
    uint8_t i, Val;
    for(i = 0; i < 8; i++)
    {
        SCL_HIGH();
        soft_i2c_Delay(WaitTime);
        Val <<= 1;
        if(READ_SDA() != 0)
        {
            Val |= 0x01;
        }
        SCL_LOW();
        soft_i2c_Delay(WaitTime);
    }
    return Val;
}
//
