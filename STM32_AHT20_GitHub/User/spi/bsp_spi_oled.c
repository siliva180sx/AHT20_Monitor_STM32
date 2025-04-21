#include "bsp_spi_oled.h"
#include "font6x8.h"

//SPI1傳送單Byte資料
static void SPI_WriteByte(uint8_t byte) {
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

//控制DC電平
static void OLED_DC(uint8_t state) {
	GPIO_WriteBit(OLED_DC_PORT, OLED_DC_PIN, (BitAction)state);
}

//控制RES電平
static void OLED_RES(uint8_t state) {
	GPIO_WriteBit(OLED_RES_PORT, OLED_RES_PIN, (BitAction)state);
}

//傳送一個指令到OLED（DC=0）然後控制OLED設定
void OLED_WriteCommand(uint8_t cmd) {
	OLED_DC(0);
	SPI_WriteByte(cmd);
}

//傳送一個byte到OLED（DC=1）然後控制顯示在畫面上的像素內容
void OLED_WriteData(uint8_t data) {
	OLED_DC(1);
	SPI_WriteByte(data);
}

/*補充
*0x10 | N 保證高 4 bits結果落在 0x10 ~ 0x1F
*N & 0x0F 保證低 4 bits結果落在 0x00 ~ 0x0F
*此函式是設定一個字元要顯示在哪一頁，X軸要從哪一列(Column)開始顯示
*/
void OLED_SetCursor(uint8_t page, uint8_t column) {
	uint8_t col = column + 2;        		 							 //SH1106 通常有「2 點左側空白」的硬體偏移所以X軸游標要先加2
	OLED_WriteCommand(0xB0 + page);   	 							 //0xB0 為SE1106內建的指令集(控制頁)
	OLED_WriteCommand(col & 0x0F);    							   //取col低4位 位元
	OLED_WriteCommand(0x10 | (col >> 4));						   //右移四個位元，取高4bit
}

//清除畫面
void OLED_Clear(void) {
	uint8_t page, col;
	for (page = 0; page < 8; page++) {      //共8個 頁
		OLED_SetCursor(page, 0);
		for (col = 0; col < 128; col++) {     //128個 Column
			OLED_WriteData(0x00);
		}
	}
}

//顯示一段ASCII字串，字模為 6x8，每個字寬6像素
void OLED_ShowString(uint8_t page, uint8_t column, char *str) {
	uint8_t i;
	while (*str) {
		if (column > 122) {                           //快超出畫面寬度128px (一個字元=6個象素點)
				column = 0;                               //從最前面開始
				page++;                                   //換下一頁
				if (page > 7) page = 0;                   //若page超過最大值7，就環回到 0（畫面從頂部重新寫）
		}
		OLED_SetCursor(page, column);                 //設定開始Column
		for (i = 0; i < 6; i++) {                     //開始寫一個字
				OLED_WriteData(Font6x8[*str - 32][i]);
		}
		column += 6;                                  //寫完Column加一個字元的寬度(設定下個字的開始Column)
		str++;                                        //載入下一個字並回到for迴圈 一直重複直到while (*str)為假才跳出函式
	}
}

//顯示° 
void OLED_ShowDegree(uint8_t page, uint8_t col) {
	uint8_t i;
	OLED_SetCursor(page, col);
	for (i = 0; i < 6; i++) {
		OLED_WriteData(DegreeSymbol6x8[i]);
	}
}

/*補充
*顯示單一英文字元，6x8 字模
*  p[i]='T' =>  SH1106排列如下(由下而上，由左而右)
*      0x01 0x01 0x7F 0x01 0x01 0x00
*  Bit0  1    1    1    1    1    0
*  Bit1  0    0    1    0    0    0
*  Bit2  0    1    1    0    0    0          
*  Bit3  0    0    1    0    0    0
*  Bit4  0    0    1    0    0    0
*  Bit5  0    0    1    0    0    0
*  Bit6  0    0    1    0    0    0
*  Bit7  0    0    1    0    0    0
*
*/

//{0x00,0x42,0x7F,0x40,0x00,0x00}, // 0x31 '1'

void OLED_ShowChar(uint8_t page, uint8_t col, char ch)
{
    uint8_t i;
    const uint8_t *p = Font6x8[ch - 32];  //對應ASCII字元陣列（從32開始）

    OLED_SetCursor(page, col);
    for (i = 0; i < 6; i++) {
        OLED_WriteData(p[i]);             //列印該字元的象素(由下而上，由左而右)
    }
}

/***************************************************************************************/

//顯示"Temp: 00.0°C"
void OLED_ShowTemperature(uint8_t page, float temp, uint8_t is_celsius){

	char tbuffer[10];
	uint8_t col = 60;

	snprintf(tbuffer, sizeof(tbuffer), "%.1f", temp);        // 將 float 轉為字串
	
	OLED_ShowString(page, 0, "Temp:");
   
	OLED_ShowString(page, 36, tbuffer);
	
	OLED_ShowDegree(page, 60);                              // 顯示 ° 符號
	col += 6;

	if (is_celsius)
		OLED_ShowChar(page, col, 'C');
	else
		OLED_ShowChar(page, col, 'F');
}

//顯示"Hum: 00.0%"
void OLED_DisplayHumidity(uint8_t page, float hum){

	char hbuffer[10];
	
	snprintf(hbuffer, sizeof(hbuffer), "%.1f", hum);        // 將 float 轉為字串
  OLED_ShowString(page, 0, "Hum:");
	
	OLED_ShowString(page, 36, hbuffer);
	
  OLED_ShowString(page, 66, "%");                         // 顯示 % 符號
}

/***************************************************************************************/

void OLED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	//開啟GPIOA，GPIOB，SPI1 的時鐘
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1, ENABLE);

	//初始化GPIO PA5(SCK腳) 和 GPIO PA7(MOSI腳)
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = OLED_SCK_PIN | OLED_MOSI_PIN;
	GPIO_Init(OLED_SCK_PORT, &GPIO_InitStruct);
	
	//初始化GPIO PB1(RES腳)
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = OLED_RES_PIN;
	GPIO_Init(OLED_RES_PORT, &GPIO_InitStruct);
	
	//初始化GPIO PB0(DC腳)
	GPIO_InitStruct.GPIO_Pin = OLED_DC_PIN;
	GPIO_Init(OLED_DC_PORT, &GPIO_InitStruct);
	
	//初始化SPI
	SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);
  
	/*確保OLED模組從乾淨狀態開機，避免不穩畫面或殘影*/
	OLED_RES(0);           //拉低RES電平，重設模組
	SysTick_delay__ms(50);  // 等待穩定重設模組
	OLED_RES(1);           // 拉高，結束重設
	SysTick_delay__ms(50);  // 等待穩定重設模組
		
	//初始化SH1106的暫存器
	OLED_WriteCommand(0xAE);
	OLED_WriteCommand(0xD5); 
	OLED_WriteCommand(0x80);
	OLED_WriteCommand(0xA8); 
	OLED_WriteCommand(0x3F);
	OLED_WriteCommand(0xD3); 
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x40);
	OLED_WriteCommand(0xAD); 
	OLED_WriteCommand(0x8B);
	OLED_WriteCommand(0x30);
	OLED_WriteCommand(0xA1);
	OLED_WriteCommand(0xC8);
	OLED_WriteCommand(0xDA); 
	OLED_WriteCommand(0x12);
	OLED_WriteCommand(0x81); 
	OLED_WriteCommand(0x7F);
	OLED_WriteCommand(0xD9); 
	OLED_WriteCommand(0x22);
	OLED_WriteCommand(0xDB); 
	OLED_WriteCommand(0x40);
	OLED_WriteCommand(0xA4);
	OLED_WriteCommand(0xA6);
	OLED_WriteCommand(0xAF);
	
	//寫入全0x00，把畫面清空
	OLED_Clear();   
}
