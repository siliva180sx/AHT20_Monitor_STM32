#include "stm32f10x.h"
#include "bsp_dma_mtp.h"
#include "bsp_aht20.h" 
#include "bsp_exti.h"  
#include "bsp_key.h"
#include "bsp_spi_oled.h" 



volatile uint8_t is_celsius = 1;

int main(void){
	uint8_t i=2;
	float usart_temp;
	float oled_temp;	
	float humi;
	char Tempbuffer[64];
	char Humibuffer[64];

	//初始化
	USART_Config();   //串列埠
  I2C1_Config();    //IIC
	SysTick_Init();   //計時器(Delay)
	KEY_GPIO_Confing();
	EXTI_KEY_Config();
	printf ("START\n");
	OLED_Init();
	
		while(i){
	// 開機畫面
	OLED_Clear();
	OLED_ShowString(3, 0, "      loading");
	SysTick_delay__ms(1000);
	OLED_Clear();
	OLED_ShowString(3, 0, "      loading.");
	SysTick_delay__ms(500);
	OLED_Clear();
	OLED_ShowString(3, 0, "      loading..");
	SysTick_delay__ms(500);
	OLED_Clear();
	OLED_ShowString(3, 0, "      loading...");
	SysTick_delay__ms(500);
	i--;			
	}
	
	OLED_Clear();
	OLED_ShowString(0, 0, "----SHT20 sensor---");

	while(1){
		//printf ("進入迴圈\n");
		usart_temp = SHT20_ReadTemperature();
		oled_temp = SHT20_ReadTemperature();
		if(is_celsius != 1){
			
			SysTick_delay__ms(10);
			
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0){
								
				float oled_temp = is_celsius ? oled_temp : (oled_temp * 1.8f + 32);
				OLED_ShowTemperature(2, oled_temp, 0);		
			
			}			
		}
		else OLED_ShowTemperature(2, oled_temp, 1);	
		
		snprintf(Tempbuffer, sizeof(Tempbuffer), "Temp: %.2f°C\n", usart_temp);
    USART1_DMA_SendString(Tempbuffer);
				
		humi = SHT20_ReadHumidity();		
		snprintf(Humibuffer, sizeof(Humibuffer), "humi: %.2f°C\n", humi);
		USART1_DMA_SendString(Humibuffer);
		
		printf("%.2f,%.2f\n", usart_temp, humi);
		
		OLED_DisplayHumidity(4, humi);

		
		SysTick_delay__ms(1000);
		
	}	
}


