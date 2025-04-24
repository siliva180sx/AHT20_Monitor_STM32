#include "bsp_systick.h"
    uint32_t i;

//SysTick初始化
void SysTick_Init(void) {
    SysTick_Config(72000);                      // 1ms中斷
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //先關閉，使用時再啟用
}

//毫秒級延時
void SysTick_delay__ms(uint32_t ms) {
    SysTick->LOAD = 72000 - 1;                  // 1ms 計時
    SysTick->VAL = 0;                           // 清除當前值
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   // 啟用 SysTick
	  
    for (i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & (1 << 16)));   // 等待 COUNTFLAG
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  // 關閉 SysTick
}

/*SysTick_Config(uint32_t reload);  
此函數內部的計算公式為:
(uint32_t reload) * 1/72M(系統時鐘) = t(計時器單位)
因STM32F103預設系統時鐘為72MHz，因此reload應為72000使其 t(計時器單位)為ms

LOAD = 72000 - 1：
計數器從 71999 → 71998 → ... → 0，共 72000 時鐘周期（正好 1ms）。
*/
 
