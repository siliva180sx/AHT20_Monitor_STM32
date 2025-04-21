#include "bsp_spi_oled.h"
#include "font6x8.h"

//SPI1�ǰe��Byte���
static void SPI_WriteByte(uint8_t byte) {
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

//����DC�q��
static void OLED_DC(uint8_t state) {
	GPIO_WriteBit(OLED_DC_PORT, OLED_DC_PIN, (BitAction)state);
}

//����RES�q��
static void OLED_RES(uint8_t state) {
	GPIO_WriteBit(OLED_RES_PORT, OLED_RES_PIN, (BitAction)state);
}

//�ǰe�@�ӫ��O��OLED�]DC=0�^�M�ᱱ��OLED�]�w
void OLED_WriteCommand(uint8_t cmd) {
	OLED_DC(0);
	SPI_WriteByte(cmd);
}

//�ǰe�@��byte��OLED�]DC=1�^�M�ᱱ����ܦb�e���W���������e
void OLED_WriteData(uint8_t data) {
	OLED_DC(1);
	SPI_WriteByte(data);
}

/*�ɥR
*0x10 | N �O�Ұ� 4 bits���G���b 0x10 ~ 0x1F
*N & 0x0F �O�ҧC 4 bits���G���b 0x00 ~ 0x0F
*���禡�O�]�w�@�Ӧr���n��ܦb���@���AX�b�n�q���@�C(Column)�}�l���
*/
void OLED_SetCursor(uint8_t page, uint8_t column) {
	uint8_t col = column + 2;        		 							 //SH1106 �q�`���u2 �I�����ťաv���w�鰾���ҥHX�b��Эn���[2
	OLED_WriteCommand(0xB0 + page);   	 							 //0xB0 ��SE1106���ت����O��(���)
	OLED_WriteCommand(col & 0x0F);    							   //��col�C4�� �줸
	OLED_WriteCommand(0x10 | (col >> 4));						   //�k���|�Ӧ줸�A����4bit
}

//�M���e��
void OLED_Clear(void) {
	uint8_t page, col;
	for (page = 0; page < 8; page++) {      //�@8�� ��
		OLED_SetCursor(page, 0);
		for (col = 0; col < 128; col++) {     //128�� Column
			OLED_WriteData(0x00);
		}
	}
}

//��ܤ@�qASCII�r��A�r�Ҭ� 6x8�A�C�Ӧr�e6����
void OLED_ShowString(uint8_t page, uint8_t column, char *str) {
	uint8_t i;
	while (*str) {
		if (column > 122) {                           //�ֶW�X�e���e��128px (�@�Ӧr��=6�ӶH���I)
				column = 0;                               //�q�̫e���}�l
				page++;                                   //���U�@��
				if (page > 7) page = 0;                   //�Ypage�W�L�̤j��7�A�N���^�� 0�]�e���q�������s�g�^
		}
		OLED_SetCursor(page, column);                 //�]�w�}�lColumn
		for (i = 0; i < 6; i++) {                     //�}�l�g�@�Ӧr
				OLED_WriteData(Font6x8[*str - 32][i]);
		}
		column += 6;                                  //�g��Column�[�@�Ӧr�����e��(�]�w�U�Ӧr���}�lColumn)
		str++;                                        //���J�U�@�Ӧr�æ^��for�j�� �@�����ƪ���while (*str)�����~���X�禡
	}
}

//��ܢX 
void OLED_ShowDegree(uint8_t page, uint8_t col) {
	uint8_t i;
	OLED_SetCursor(page, col);
	for (i = 0; i < 6; i++) {
		OLED_WriteData(DegreeSymbol6x8[i]);
	}
}

/*�ɥR
*��ܳ�@�^��r���A6x8 �r��
*  p[i]='T' =>  SH1106�ƦC�p�U(�ѤU�ӤW�A�ѥ��ӥk)
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
    const uint8_t *p = Font6x8[ch - 32];  //����ASCII�r���}�C�]�q32�}�l�^

    OLED_SetCursor(page, col);
    for (i = 0; i < 6; i++) {
        OLED_WriteData(p[i]);             //�C�L�Ӧr�����H��(�ѤU�ӤW�A�ѥ��ӥk)
    }
}

/***************************************************************************************/

//���"Temp: 00.0�XC"
void OLED_ShowTemperature(uint8_t page, float temp, uint8_t is_celsius){

	char tbuffer[10];
	uint8_t col = 60;

	snprintf(tbuffer, sizeof(tbuffer), "%.1f", temp);        // �N float �ର�r��
	
	OLED_ShowString(page, 0, "Temp:");
   
	OLED_ShowString(page, 36, tbuffer);
	
	OLED_ShowDegree(page, 60);                              // ��� �X �Ÿ�
	col += 6;

	if (is_celsius)
		OLED_ShowChar(page, col, 'C');
	else
		OLED_ShowChar(page, col, 'F');
}

//���"Hum: 00.0%"
void OLED_DisplayHumidity(uint8_t page, float hum){

	char hbuffer[10];
	
	snprintf(hbuffer, sizeof(hbuffer), "%.1f", hum);        // �N float �ର�r��
  OLED_ShowString(page, 0, "Hum:");
	
	OLED_ShowString(page, 36, hbuffer);
	
  OLED_ShowString(page, 66, "%");                         // ��� % �Ÿ�
}

/***************************************************************************************/

void OLED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	//�}��GPIOA�AGPIOB�ASPI1 ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1, ENABLE);

	//��l��GPIO PA5(SCK�}) �M GPIO PA7(MOSI�})
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = OLED_SCK_PIN | OLED_MOSI_PIN;
	GPIO_Init(OLED_SCK_PORT, &GPIO_InitStruct);
	
	//��l��GPIO PB1(RES�})
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = OLED_RES_PIN;
	GPIO_Init(OLED_RES_PORT, &GPIO_InitStruct);
	
	//��l��GPIO PB0(DC�})
	GPIO_InitStruct.GPIO_Pin = OLED_DC_PIN;
	GPIO_Init(OLED_DC_PORT, &GPIO_InitStruct);
	
	//��l��SPI
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
  
	/*�T�OOLED�Ҳձq���b���A�}���A�קK��í�e���δݼv*/
	OLED_RES(0);           //�ԧCRES�q���A���]�Ҳ�
	SysTick_delay__ms(50);  // ����í�w���]�Ҳ�
	OLED_RES(1);           // �԰��A�������]
	SysTick_delay__ms(50);  // ����í�w���]�Ҳ�
		
	//��l��SH1106���Ȧs��
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
	
	//�g�J��0x00�A��e���M��
	OLED_Clear();   
}
