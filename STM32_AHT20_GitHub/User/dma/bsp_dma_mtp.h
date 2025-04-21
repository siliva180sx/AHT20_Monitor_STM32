#ifndef __BSP_DMA_MTP_H
#define __BSP_DMA_MTP_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include <stdio.h>                   //須包含此頭文件以利使用fputc函式進行數據重定向
#include <string.h>



#define DEBUG_USARTx             	 	  USART1                              
#define DEBUG_USART_CLK 							RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd 				RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE					115200

#define DEBUG_USART_GPIO_CLK					(RCC_APB2Periph_GPIOA)
#define DEBUG_USART_GPIO_APBxClkCmd		RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT			GPIOA
#define DEBUG_USART_TX_GPIO_PIN				GPIO_Pin_9
#define DEBUG_USART_RX_GPIO_PORT			GPIOA	
#define DEBUG_USART_RX_GPIO_PIN				GPIO_Pin_10

#define USART_TX_DMA_CLk  	  RCC_AHBPeriph_DMA1
#define USART_TX_CHANNEL 		   DMA1_Channel4
#define USART_TX_DMA_FLAG_TC	DMA1_FLAG_TC4
#define USART_DR_ADDRESS			(USART1->DR)								


void USART_Config(void);
void USART1_DMA_SendString(char *str);

#endif /*__BSP_LED_H*/

