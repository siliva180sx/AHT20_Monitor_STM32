#include "bsp_key.h"


void KEY_GPIO_Confing(void){                               
  
	//�w�q�@�Ӫ�l�Ƶ��c��GPIO_Initstruct�ýեμзǮw����GPIO_InitTypeDef�H�K�ϥΨ䤺���]�w�Ѽ�
	GPIO_InitTypeDef GPIO_Initstruct;                        
	
	//�]�wKEY1�������w�}��(���APB2��RCC����)
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);

	//�]�wGPIO Pin�}��GPIO_Pin_0	
	GPIO_Initstruct.GPIO_Pin  = KEY1_GPIO_PIN;
	
	//�]�wGPIO�Ҧ�(GPIO_Pin_0)���B�ſ�J	
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	//�եμзǮw���禡GPIO_Init������l��(�ǤJGPIO���ݤf�AGPIO_Initstruct���}��ǤJ)
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_Initstruct);             

}                                                          



