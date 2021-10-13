#include "bsp24C02.h"
#include "softI2C.h"

#define AT24C02

#define DevWRAdd 0xA0
#define DevRDAdd (DevWRAdd|0x01)


uint8_t EEP_GetLock()
{
    return HAL_GPIO_ReadPin(EWP_GPIO_Port, EWP_Pin);
}

void EEP_SetLock(uint8_t state)
{
    if(state)
    {
        HAL_GPIO_WritePin(EWP_GPIO_Port, EWP_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(EWP_GPIO_Port, EWP_Pin, GPIO_PIN_RESET);
    }
}


uint8_t EEP_Read_Byte(uint16_t Address)
{
    uint8_t dat = 0;
    soft_i2c_Start();
    soft_i2c_Write_Byte(DevWRAdd);
    soft_i2c_Send_ACK();

#if defined(AT24C01) || defined(AT24C02)
    if(Address > 255) return 0x00;
#else
    I2C_Write_Byte((Address >> 8) & 0xff);
    I2C_Send_ACK();
#endif
    soft_i2c_Write_Byte((uint8_t)Address);
    soft_i2c_Send_ACK();
    soft_i2c_Start();
    soft_i2c_Write_Byte(DevRDAdd);
    soft_i2c_Send_ACK();
    dat = soft_i2c_Read_Byte();
    soft_i2c_Stop();
    return dat;
}


void EEP_Write_Byte(uint16_t Address, uint8_t dat)
{
    if(EEP_GetLock() == ENABLE)
    {
        return;
    }
    soft_i2c_Start();
    soft_i2c_Write_Byte(DevWRAdd);
    soft_i2c_Send_ACK();

#if defined(AT24C01) || defined(AT24C02)
    if(Address > 255) Address = 255;
#else
    I2C_Write_Byte((Address >> 8) & 0xff);
    I2C_Send_ACK();
#endif
    soft_i2c_Write_Byte((uint8_t)Address);
    soft_i2c_Send_ACK();
    soft_i2c_Write_Byte(dat);
    soft_i2c_Send_ACK();
    soft_i2c_Stop();
    HAL_Delay(3);
}





