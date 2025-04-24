#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h"                                 //�]�U��w�q���������w�q��stm32f10x.h�����������]���ݦb���n�����Y���

#define KEY1_INT_GPIO_PORT     GPIOA
#define KEY1_INT_GPIO_PIN      GPIO_Pin_0
#define KEY1_INT_GPIO_CLK   	 RCC_APB2Periph_GPIOA

void EXTI_KEY_Config(void);                             //�Nbsp_exti.c���禡���Y���i���n���H�Q�� main.c �D�{���ե�


#endif /*__BSP_EXTI_H*/

