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

void OLED_Init(void);                            					   // 初始化 OLED 顯示器
void OLED_Clear(void);                           					   // 清除畫面
void OLED_SetCursor(uint8_t page, uint8_t col); 			  	   // 設定游標位置
void OLED_WriteCommand(uint8_t cmd);            					   // 寫入指令
void OLED_WriteData(uint8_t data);               					   // 寫入資料
void OLED_ShowString(uint8_t page, uint8_t col, char *str);  // 顯示一行文字
void OLED_ShowDegree(uint8_t page, uint8_t col);
void OLED_ShowChar(uint8_t page, uint8_t col, char ch);

void OLED_DisplayHumidity(uint8_t page, float hum);
void OLED_ShowTemperature(uint8_t page, float temp, uint8_t is_celsius);

#endif /* __BSP_SPI_OLED_H */

