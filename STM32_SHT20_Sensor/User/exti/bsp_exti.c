#include "bsp_exti.h"

static void EXTI_NVIC_Config(void){                             //�إߪ�l��NVIC�禡�H�QEXTI_KEY_Config(void)�ե�
	
	//�ե�msic.h����ƨæ۩w�q�@�Ө�ƥH�K�i��NVIC_InitTypeDef�禡�����Ѽƪ��ե�
	NVIC_InitTypeDef NVIC_Initstruct;
	
	//�]�wNVIC�u���ŲէO(1)
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);              
	
	//�]�w���˴������_��(EXTI0_IRQn)�ݰѦ�stm32f10x.h ��186��]���˴���PINú��PA"0"�]���ݿ��EXTI0�o���˴��u����IRQ�q�D
	NVIC_Initstruct.NVIC_IRQChannel = EXTI0_IRQn;                 
	
	//�]�w�m�e�u����(1)
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority = 1;        
	
	//�]�w�l�u����(1)
	NVIC_Initstruct.NVIC_IRQChannelSubPriority = 1;
	
	//�}�Ҧ����_�\��
	NVIC_Initstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//�NNVIC_Initstruct�o�Ө�ƪ��a�}�ᤩ��NVIC_Init�o�Ө禡�èϥΨ�禡�\��i���l��NVIC 
	NVIC_Init(&NVIC_Initstruct);
	
}
 
void EXTI_KEY_Config(void){
	
	//�ե�stm32f10x_gpio.h����ƨæ۩w�q�@�Ө�ƥH�K�i��GPIO_InitTypeDef�禡�����Ѽƪ��ե�	
	GPIO_InitTypeDef GPIO_Initstruct;
  
	//�ե�stm32f10x_exti.h����ƨæ۩w�q�@�Ө�ƥH�K�i��EXTI_InitTypeDef�禡�����Ѽƪ��ե�
	EXTI_InitTypeDef EXTI_Initstruct;
	
	//�إߪ�l��NVIC�禡�H�Qmain.c �D�禡�ե�
	EXTI_NVIC_Config();              
	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);	       //�}�Ҷ��˴����_GPIO�}�쪺����
	GPIO_Initstruct.GPIO_Pin  = KEY1_INT_GPIO_PIN;  		       //�]�w���˴����_GPIO�}�쪺PIN�}
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;		     //�]�w���˴����_GPIO�}�쪺�Ҧ�(�B�ſ�J)
	
	//�ǤJ���˴����_GPIO�}�쪺�ݤf�H��GPIO_Initstruct�o�Ө�ƪ��a�}��GPIO_Init�o�Ө禡�èϥΨ�禡�\��i���l��GPIO�޸}	
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_Initstruct);
  	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	        //�}��AFIO������
	
	//�ե�GPIO_EXTILineConfig()�o�Ө�ƱN���w�� GPIO �}��]�p PA0�^ �P EXTI ���_�u�]�p EXTI0�^ �j�w�A�ϸӸ}�쪺�T���ܤƯ�Ĳ�o�~�����_�C
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOA,  GPIO_PinSource0); 
	
	EXTI_Initstruct.EXTI_Line = EXTI_Line0;                     //�]�w�˴��u��EXTI_Line0
	EXTI_Initstruct.EXTI_Mode = EXTI_Mode_Interrupt;            //�]�w�˴��Ҧ���(���_/�ƥ�)���_ 
	EXTI_Initstruct.EXTI_Trigger = EXTI_Trigger_Rising;         //�]�w���_Ĳ�o�q����(�W�ɪu/�U���u)�W�ɪu
	//EXTI_Initstruct.EXTI_Trigger = EXTI_Trigger_Falling;      //�]�w���_Ĳ�o�q����(�W�ɪu/�U���u)�U���u
	EXTI_Initstruct.EXTI_LineCmd = ENABLE;                      //�}��EXTI���_Ĳ�o�\��
	EXTI_Init(&EXTI_Initstruct);                                //�NEXTI_Initstruct�o�Ө�ƪ��a�}�ᤩ��EXTI_Init�o�Ө禡�èϥΨ�禡�\��i���l��EXTI

}

/* 
  �ɥR:
  EXTI �t�d�u�����q���ܤơv�ò��ͤ��_�ШD�C

  NVIC �t�d�u�޲z���_�u���šv�M�u����줤�_��ơv�C
  
 �U���X�F�m���u���v�M�l�u���v�����\��
 The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
            
    NVIC�u���ŲէO       | NVIC�m�e�u����                    | NVIC�l�u����                | �줸�y�z
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



