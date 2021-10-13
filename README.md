# PEAK PCAN firmware for STM32F072 based boards

## 软件
- 软件修改自 [pcan_cantact](https://github.com/moonglow/pcan_cantact) 
- 增加 24C02 存储器实现 PCAN-View 中的设备 ID 设置功能

## 硬件
- 硬件在CANable基础上增加 24C02 存储器
	- PB13：24C02 - WP
	- PB14：24C02 - SCL
	- PB15：24C02 - SDA 
- 因程序大小超出 STM32F042C6 存储器容量，应使用 STM32F072C8

## 环境

- MDK-ARM V5.33


License
----

WTFPL

