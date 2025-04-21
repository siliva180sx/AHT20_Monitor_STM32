#include "bsp_aht20.h" 

void I2C1_Config(void){
	
	I2C_InitTypeDef I2C1_InitStruct;
	GPIO_InitTypeDef GPIOB_InitStruct;
	
  //開啟I2C1和GPIOB的時鐘	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//初始化IIC1 SDA
	GPIOB_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIOB_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD; //復用開漏
	GPIOB_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_InitStruct);
	
	//初始化IIC1 SCL
	GPIOB_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIOB_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIOB_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_InitStruct);
	
	//初始化IIC1
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

    uint8_t msb, lsb;       //存第一個和第二個位元組的資料的變數
    uint16_t raw;           //暫存兩個位元資料合併的變數
    float temp; 
	
		SysTick_Init();
		
    // Start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
		//printf ("起始訊號成功\n");

	
    // 發送 SHT20 地址 + Write
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // 發送溫度命令 0xF3
    I2C_SendData(I2C1, TRIG_TEMP);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // Stop
    I2C_GenerateSTOP(I2C1, ENABLE);

    // Delay 等待資料準備
    SysTick_delay__ms(100);

    // 第二次start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // 發送地址 + Read
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    // 讀 MSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    msb = I2C_ReceiveData(I2C1);

    // 讀 LSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    lsb = I2C_ReceiveData(I2C1);

    // 關閉發送響應訊號和開啟停止訊號
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    // 合併資料(先把msb強制轉換為16Bit的容器並把數據左移8位後在加上去除兩位位元(status bits)的lsb)
    raw = ((uint16_t)msb << 8) | (lsb & 0xFC);
    temp = -46.85 + 175.72 * (float)raw / 65536.0;

    // 開啟發送響應訊號ACK
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return temp;
}

float SHT20_ReadHumidity(void){

    uint8_t msb, lsb;       //存第一個和第二個位元組的資料的變數
    uint16_t raw;           //暫存兩個位元資料合併的變數
    float humidity; 
	
		SysTick_Init();
	
    // Start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
		//printf ("起始訊號成功\n");
		
    // 發送 SHT20 地址(0x40) + Write
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // 發送溼度命令 0xF5
    I2C_SendData(I2C1, TRIG_HUMI);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    // Stop
    I2C_GenerateSTOP(I2C1, ENABLE);

    // Delay 等待資料準備
    SysTick_delay__ms(100);

    // 第二次start
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    // 發送地址 + Read
    I2C_Send7bitAddress(I2C1, SHT20_ADDR << 1, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    // 讀 MSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    msb = I2C_ReceiveData(I2C1);

    // 讀 LSB
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    lsb = I2C_ReceiveData(I2C1);

    // 關閉發送響應訊號和開啟停止訊號
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    // 合併資料(先把msb強制轉換為16Bit的容器並把數據左移8位後 + 去除兩位位元(status bits)的lsb)
    raw = ((uint16_t)msb << 8) | (lsb & 0xFC);
    humidity = -6.0 + 125.0 * (float)raw / 65536.0;
    // 開啟發送響應訊號ACK
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return humidity;
}

