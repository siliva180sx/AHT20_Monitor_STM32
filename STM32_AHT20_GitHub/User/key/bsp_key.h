#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"

#define KEY_ON     1
#define KEY_Off    0

#define KEY1_GPIO_PORT   GPIOA
#define KEY1_GPIO_PIN   GPIO_Pin_0
#define KEY1_GPIO_CLK   RCC_APB2Periph_GPIOA

void KEY_GPIO_Confing(void);                               //�b���Y�����n�����禡�H�Qmain.c���ե�
uint8_t Key_scan (GPIO_TypeDef *GPIO, uint16_t GPIO_Pin);  //�b���Y�����n�����禡�H�Qmain.c���ե�

#endif /*__BSP_KEY_H*/

