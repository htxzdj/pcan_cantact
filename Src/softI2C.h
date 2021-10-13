#ifndef __SOFT_I2C_H_
#define __SOFT_I2C_H_
#include "stm32f0xx_hal.h"

/* IO */
#define ESDA_GPIO_Port  GPIOB
#define ESDA_Pin        GPIO_PIN_15
#define ESCL_GPIO_Port  GPIOB
#define ESCL_Pin        GPIO_PIN_14
#define EWP_GPIO_Port   GPIOB
#define EWP_Pin         GPIO_PIN_13

#define SCL_HIGH()  ESCL_GPIO_Port->BSRR=ESCL_Pin
#define SCL_LOW()   ESCL_GPIO_Port->BRR=ESCL_Pin
#define SDA_HIGH()  ESDA_GPIO_Port->BSRR=ESDA_Pin
#define SDA_LOW()   ESDA_GPIO_Port->BRR=ESDA_Pin
#define READ_SDA()  (ESDA_GPIO_Port->IDR&ESDA_Pin)


void soft_i2c_Delay(uint16_t xus);

void soft_i2c_init(void);
void soft_i2c_Start(void);
void soft_i2c_Stop(void);
uint8_t soft_i2c_Wait_ACK(void);
void soft_i2c_Send_ACK(void);
void soft_i2c_Send_NACK(void);
void soft_i2c_Write_Byte(uint8_t Val);
uint8_t soft_i2c_Read_Byte(void);

#endif
