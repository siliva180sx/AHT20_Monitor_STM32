#include "bsp_key.h"


void KEY_GPIO_Confing(void){                               
  
	//定義一個初始化結構體GPIO_Initstruct並調用標準庫中的GPIO_InitTypeDef以便使用其內部設定參數
	GPIO_InitTypeDef GPIO_Initstruct;                        
	
	//設定KEY1的時鐘定開啟(位於APB2的RCC時鐘)
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);

	//設定GPIO Pin腳為GPIO_Pin_0	
	GPIO_Initstruct.GPIO_Pin  = KEY1_GPIO_PIN;
	
	//設定GPIO模式(GPIO_Pin_0)為浮空輸入	
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	//調用標準庫的函式GPIO_Init完成初始化(傳入GPIO的端口，GPIO_Initstruct取址後傳入)
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_Initstruct);             

}                                                          



