#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h"                                 //因下方定義巨集有重定義到stm32f10x.h內部的巨集因此需在此聲明此頭文件

#define KEY1_INT_GPIO_PORT     GPIOA
#define KEY1_INT_GPIO_PIN      GPIO_Pin_0
#define KEY1_INT_GPIO_CLK   	 RCC_APB2Periph_GPIOA

void EXTI_KEY_Config(void);                             //將bsp_exti.c的函式於此頭文件進行聲明以利於 main.c 主程式調用


#endif /*__BSP_EXTI_H*/

