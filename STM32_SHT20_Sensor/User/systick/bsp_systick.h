#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_delay__ms(uint32_t ms);      //�n��bsp_systick.c ��󪺩��ɨ�ƥH�Kmain.c�D�{���ե�
void SysTick_Init(void);

#endif /*__BSP_SYSTICK_H*/


