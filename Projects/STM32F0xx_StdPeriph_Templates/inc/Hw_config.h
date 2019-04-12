/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Platform config -----------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "Macro.h"
#include "stm32f0xx.h"
#include <stdio.h>

#include "Custom_SPI_TLC59025.h"
/* Define config -------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/
enum
{
	LED1 = 0x00,
	LED2 ,
	LED3 ,
	LED4 ,
	LED5 ,	
};


/* Exported types ------------------------------------------------------------*/
extern __IO uint8_t UartRxBuffer;
extern __IO uint8_t UartRxFlag;
extern const uint32_t RGBColorTable[];

void LEDx_Handler(uint8_t LEDx,uint32_t Hex);

void configTIM17(void);

void Delay(__IO uint32_t mTime);

void createUSARTTest(void);
void configUSART(void);

void configSysTick(void);
void TimingDelay_Decrement(void);
/* Exported constants --------------------------------------------------------*/

#endif  /* __HW_CONFIG_H */

