#include "bsp_aht20.h" 

void I2C1_Config(void){
	
	I2C_InitTypeDef I2C1_InitStruct;
	GPIO_InitTypeDef GPIOB_InitStruct;
	
  //�}��I2C1�MGPIOB������	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//��l��IIC1 SDA
	GPIOB_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIOB_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD; //�_�ζ}�|
	GPIOB_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_InitStruct);
	
	//��l��IIC1 SCL
	GPIOB_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIOB_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIOB_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_InitStruct);
	
	//��l��IIC1
	I2C1_InitStruct.I2C_ClockSpeed = 400000;
	I2C1_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C1_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C1_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C1_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C1_InitStruct.I2C_Ack = ENABLE;
	I2C_Init(I2C1, &I2C1_InitStruct);
	I2C_Cmd(I2C1, ENABLE);
	
}


float SHT20_ReadTemperature(void){

    uint8_t msb, lsb;       //�s�Ĥ@�өM�ĤG�Ӧ줸�ժ���ƪ��ܼ�
    uint16_t raw;           //�Ȧs��Ӧ줸��ƦX�֪��ܼ�
    float temp; 
	
		SysTick_Init();
		
    // Start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
		//printf ("�_�l�T�����\\n");

	
    // �o�e SHT20 �a�} + Write
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // �o�e�ūשR�O 0xF3
    I2C_SendData(I2C1, TRIG_TEMP);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // Stop
    I2C_GenerateSTOP(I2C1, ENABLE);

    // Delay ���ݸ�Ʒǳ�
    SysTick_delay__ms(100);

    // �ĤG��start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // �o�e�a�} + Read
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    // Ū MSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    msb = I2C_ReceiveData(I2C1);

    // Ū LSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    lsb = I2C_ReceiveData(I2C1);

    // �����o�e�T���T���M�}�Ұ���T��
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    // �X�ָ��(����msb�j���ഫ��16Bit���e���ç�ƾڥ���8���b�[�W�h�����줸(status bits)��lsb)
    raw = ((uint16_t)msb << 8) | (lsb & 0xFC);
    temp = -46.85 + 175.72 * (float)raw / 65536.0;

    // �}�ҵo�e�T���T��ACK
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return temp;
}

float SHT20_ReadHumidity(void){

    uint8_t msb, lsb;       //�s�Ĥ@�өM�ĤG�Ӧ줸�ժ���ƪ��ܼ�
    uint16_t raw;           //�Ȧs��Ӧ줸��ƦX�֪��ܼ�
    float humidity; 
	
		SysTick_Init();
	
    // Start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
		//printf ("�_�l�T�����\\n");
		
    // �o�e SHT20 �a�}(0x40) + Write
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // �o�e�ëשR�O 0xF5
    I2C_SendData(I2C1, TRIG_HUMI);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // Stop
    I2C_GenerateSTOP(I2C1, ENABLE);

    // Delay ���ݸ�Ʒǳ�
    SysTick_delay__ms(100);

    // �ĤG��start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // �o�e�a�} + Read
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    // Ū MSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    msb = I2C_ReceiveData(I2C1);

    // Ū LSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    lsb = I2C_ReceiveData(I2C1);

    // �����o�e�T���T���M�}�Ұ���T��
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    // �X�ָ��(����msb�j���ഫ��16Bit���e���ç�ƾڥ���8��� + �h�����줸(status bits)��lsb)
    raw = ((uint16_t)msb << 8) | (lsb & 0xFC);
    humidity = -6.0 + 125.0 * (float)raw / 65536.0;
    // �}�ҵo�e�T���T��ACK
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return humidity;
}

