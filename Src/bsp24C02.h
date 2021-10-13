#ifndef __AT24C02_H_
#define __AT24C02_H_
#include "stm32f0xx_hal.h"

uint8_t EEP_GetLock(void);
void EEP_SetLock(uint8_t state);
uint8_t EEP_Read_Byte(uint16_t Address);
void EEP_Write_Byte(uint16_t Address, uint8_t dat);

//uint8_t EEP_Check(void);
//uint16_t BSP_ReadEEPData(void);
//void BSP_WriteEEPData(uint8_t DA1, uint8_t DA2);


#endif
