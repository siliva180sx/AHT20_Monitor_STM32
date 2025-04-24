#include "bsp_dma_mtp.h"

void USART_Config(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  //�}��GPIO�MUSART������
  DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
  DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

  //�]�wTX�]PA9�^���_�α�����X
  GPIO_InitStruct.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                  // �_�α���
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

  //�]�w RX�]PA10�^���B�ſ�J
  GPIO_InitStruct.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;                            // �B�ſ�J
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);

  //�]�wUSART�Ѽ�
  USART_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE;         					    // �j�v
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;            			  	// 8����
  USART_InitStruct.USART_StopBits = USART_StopBits_1;                 			  	//1�찱���
  USART_InitStruct.USART_Parity = USART_Parity_No;                              // ���ϥή���
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // �L�w��y��
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;          			  // �ҥΦ��o�Ҧ�
  USART_Init(DEBUG_USARTx, &USART_InitStruct);                          			  // ��l�� USART1

  //�ҥ�USART1��DMA�ǰe�ШD�\��
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);

  //�ҥ�USART�~�]
  USART_Cmd(DEBUG_USARTx, ENABLE);
}

void USART1_DMA_SendString(char *str){
  DMA_InitTypeDef DMA_InitStruct;

  //�ҥ�DMA1���������
  RCC_AHBPeriphClockCmd(USART_TX_DMA_CLk, ENABLE);

  //�T�O�q�D��l�ƫe������
  DMA_Cmd(USART_TX_CHANNEL, DISABLE);

  //��l��DMA
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)USART_DR_ADDRESS;    // USART1 ��ƼȦs��
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)str;                     // �r��O����_�l��m
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;                        // �]�w��Ƥ�V�G�O���� => �~�]
  DMA_InitStruct.DMA_BufferSize = strlen(str);                           // �ǰe����ƪ��ס]�r���ơ^
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;          // USART �H�s������++
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   // �~�]��Ƥj�p�G1 Byte
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                   // �O����a�}�ۼW
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           // �O�����Ƥj�p�G1 Byte
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;                             // ���`�Ҧ��]�D�`���^
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;                       // ���u���v
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                              // �����O�����O����Ҧ�
 
  //��lDMA
  DMA_Init(USART_TX_CHANNEL, &DMA_InitStruct);

  //�M���ǰe�����X�СA�קK�z�Z
  DMA_ClearFlag(USART_TX_DMA_FLAG_TC);

  //�ҥ�DMA�}�l�ǰe
  DMA_Cmd(USART_TX_CHANNEL, ENABLE);
}

int fputc (int ch, FILE *f){ 
  USART_SendData(DEBUG_USARTx, (uint8_t)ch);                              // �o�e�@�Ӧr��
  while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);      // ���ݵo�e����
  return ch;
}
