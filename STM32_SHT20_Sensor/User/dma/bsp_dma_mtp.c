#include "bsp_dma_mtp.h"

void USART_Config(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  //開啟GPIO和USART的時鐘
  DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
  DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

  //設定TX（PA9）為復用推挽輸出
  GPIO_InitStruct.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                  // 復用推挽
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

  //設定 RX（PA10）為浮空輸入
  GPIO_InitStruct.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;                            // 浮空輸入
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);

  //設定USART參數
  USART_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE;         					    // 鮑率
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;            			  	// 8位資料
  USART_InitStruct.USART_StopBits = USART_StopBits_1;                 			  	//1位停止位
  USART_InitStruct.USART_Parity = USART_Parity_No;                              // 不使用校驗
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // 無硬體流控
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;          			  // 啟用收發模式
  USART_Init(DEBUG_USARTx, &USART_InitStruct);                          			  // 初始化 USART1

  //啟用USART1的DMA傳送請求功能
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);

  //啟用USART外設
  USART_Cmd(DEBUG_USARTx, ENABLE);
}

void USART1_DMA_SendString(char *str){
  DMA_InitTypeDef DMA_InitStruct;

  //啟用DMA1控制器的時鐘
  RCC_AHBPeriphClockCmd(USART_TX_DMA_CLk, ENABLE);

  //確保通道初始化前先關閉
  DMA_Cmd(USART_TX_CHANNEL, DISABLE);

  //初始化DMA
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)USART_DR_ADDRESS;    // USART1 資料暫存器
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)str;                     // 字串記憶體起始位置
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;                        // 設定資料方向：記憶體 => 外設
  DMA_InitStruct.DMA_BufferSize = strlen(str);                           // 傳送的資料長度（字元數）
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;          // USART 寄存器不能++
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   // 外設資料大小：1 Byte
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                   // 記憶體地址自增
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           // 記憶體資料大小：1 Byte
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;                             // 正常模式（非循環）
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;                       // 高優先權
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                              // 關閉記憶體到記憶體模式
 
  //初始DMA
  DMA_Init(USART_TX_CHANNEL, &DMA_InitStruct);

  //清除傳送完成旗標，避免干擾
  DMA_ClearFlag(USART_TX_DMA_FLAG_TC);

  //啟用DMA開始傳送
  DMA_Cmd(USART_TX_CHANNEL, ENABLE);
}

int fputc (int ch, FILE *f){ 
  USART_SendData(DEBUG_USARTx, (uint8_t)ch);                              // 發送一個字元
  while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);      // 等待發送完成
  return ch;
}
