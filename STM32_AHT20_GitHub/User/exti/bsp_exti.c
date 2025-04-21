#include "bsp_exti.h"

static void EXTI_NVIC_Config(void){                             //建立初始化NVIC函式以利EXTI_KEY_Config(void)調用
	
	//調用msic.h的函數並自定義一個函數以便進行NVIC_InitTypeDef函式內部參數的調用
	NVIC_InitTypeDef NVIC_Initstruct;
	
	//設定NVIC優先級組別(1)
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);              
	
	//設定須檢測的中斷源(EXTI0_IRQn)需參考stm32f10x.h 第186行因須檢測的PIN繳為PA"0"因此需選擇EXTI0這條檢測線中的IRQ通道
	NVIC_Initstruct.NVIC_IRQChannel = EXTI0_IRQn;                 
	
	//設定搶占優先級(1)
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority = 1;        
	
	//設定子優先級(1)
	NVIC_Initstruct.NVIC_IRQChannelSubPriority = 1;
	
	//開啟此中斷功能
	NVIC_Initstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//將NVIC_Initstruct這個函數的地址賦予給NVIC_Init這個函式並使用其函式功能進行初始化NVIC 
	NVIC_Init(&NVIC_Initstruct);
	
}
 
void EXTI_KEY_Config(void){
	
	//調用stm32f10x_gpio.h的函數並自定義一個函數以便進行GPIO_InitTypeDef函式內部參數的調用	
	GPIO_InitTypeDef GPIO_Initstruct;
  
	//調用stm32f10x_exti.h的函數並自定義一個函數以便進行EXTI_InitTypeDef函式內部參數的調用
	EXTI_InitTypeDef EXTI_Initstruct;
	
	//建立初始化NVIC函式以利main.c 主函式調用
	EXTI_NVIC_Config();              
	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);	       //開啟須檢測中斷GPIO腳位的時鐘
	GPIO_Initstruct.GPIO_Pin  = KEY1_INT_GPIO_PIN;  		       //設定須檢測中斷GPIO腳位的PIN腳
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;		     //設定須檢測中斷GPIO腳位的模式(浮空輸入)
	
	//傳入須檢測中斷GPIO腳位的端口以及GPIO_Initstruct這個函數的地址給GPIO_Init這個函式並使用其函式功能進行初始化GPIO引腳	
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_Initstruct);
  	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	        //開啟AFIO的時鐘
	
	//調用GPIO_EXTILineConfig()這個函數將指定的 GPIO 腳位（如 PA0） 與 EXTI 中斷線（如 EXTI0） 綁定，使該腳位的訊號變化能觸發外部中斷。
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOA,  GPIO_PinSource0); 
	
	EXTI_Initstruct.EXTI_Line = EXTI_Line0;                     //設定檢測線為EXTI_Line0
	EXTI_Initstruct.EXTI_Mode = EXTI_Mode_Interrupt;            //設定檢測模式為(中斷/事件)中斷 
	EXTI_Initstruct.EXTI_Trigger = EXTI_Trigger_Rising;         //設定中斷觸發電平為(上升沿/下降沿)上升沿
	//EXTI_Initstruct.EXTI_Trigger = EXTI_Trigger_Falling;      //設定中斷觸發電平為(上升沿/下降沿)下降沿
	EXTI_Initstruct.EXTI_LineCmd = ENABLE;                      //開啟EXTI中斷觸發功能
	EXTI_Init(&EXTI_Initstruct);                                //將EXTI_Initstruct這個函數的地址賦予給EXTI_Init這個函式並使用其函式功能進行初始化EXTI

}

/* 
  補充:
  EXTI 負責「偵測電平變化」並產生中斷請求。

  NVIC 負責「管理中斷優先級」和「跳轉到中斷函數」。
  
 下表給出了搶佔優先權和子優先權的允許值
 The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
            
    NVIC優先級組別       | NVIC搶占優先級                    | NVIC子優先級                | 位元描述
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
*/



