#ifndef __BSP_SHT20
#define __BSP_SHT20

#include "stm32f10x.h"  
#include "bsp_systick.h"

#define SHT20_ADDR  0x40
#define TRIG_TEMP   0xF3
#define TRIG_HUMI   0xF5

void I2C1_Config(void);
float SHT20_ReadTemperature(void);
float SHT20_ReadHumidity(void);

#endif /*__BSP _SHT20 */
