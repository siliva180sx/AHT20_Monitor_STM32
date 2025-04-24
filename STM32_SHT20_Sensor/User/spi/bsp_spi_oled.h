#ifndef __BSP_SPI_OLED_H
#define __BSP_SPI_OLED_H

#include "stm32f10x.h"
#include "bsp_systick.h"
#include <string.h>
#include <stdio.h>

#define OLED_SCK_PIN   GPIO_Pin_5   // PA5
#define OLED_MOSI_PIN  GPIO_Pin_7   // PA7
#define OLED_RES_PIN   GPIO_Pin_1   // PB1
#define OLED_DC_PIN    GPIO_Pin_0   // PB0

#define OLED_SCK_PORT  GPIOA
#define OLED_MOSI_PORT GPIOA
#define OLED_RES_PORT  GPIOB
#define OLED_DC_PORT   GPIOB

void OLED_Init(void);                            					   // ��l�� OLED ��ܾ�
void OLED_Clear(void);                           					   // �M���e��
void OLED_SetCursor(uint8_t page, uint8_t col); 			  	   // �]�w��Ц�m
void OLED_WriteCommand(uint8_t cmd);            					   // �g�J���O
void OLED_WriteData(uint8_t data);               					   // �g�J���
void OLED_ShowString(uint8_t page, uint8_t col, char *str);  // ��ܤ@���r
void OLED_ShowDegree(uint8_t page, uint8_t col);
void OLED_ShowChar(uint8_t page, uint8_t col, char ch);

void OLED_DisplayHumidity(uint8_t page, float hum);
void OLED_ShowTemperature(uint8_t page, float temp, uint8_t is_celsius);

#endif /* __BSP_SPI_OLED_H */

