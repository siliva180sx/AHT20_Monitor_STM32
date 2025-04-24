#include "bsp_systick.h"
    uint32_t i;

//SysTick��l��
void SysTick_Init(void) {
    SysTick_Config(72000);                      // 1ms���_
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //�������A�ϥήɦA�ҥ�
}

//�@��ũ���
void SysTick_delay__ms(uint32_t ms) {
    SysTick->LOAD = 72000 - 1;                  // 1ms �p��
    SysTick->VAL = 0;                           // �M����e��
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   // �ҥ� SysTick
	  
    for (i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & (1 << 16)));   // ���� COUNTFLAG
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  // ���� SysTick
}

/*SysTick_Config(uint32_t reload);  
����Ƥ������p�⤽����:
(uint32_t reload) * 1/72M(�t�ή���) = t(�p�ɾ����)
�]STM32F103�w�]�t�ή�����72MHz�A�]��reload����72000�Ϩ� t(�p�ɾ����)��ms

LOAD = 72000 - 1�G
�p�ƾ��q 71999 �� 71998 �� ... �� 0�A�@ 72000 �����P���]���n 1ms�^�C
*/
 
