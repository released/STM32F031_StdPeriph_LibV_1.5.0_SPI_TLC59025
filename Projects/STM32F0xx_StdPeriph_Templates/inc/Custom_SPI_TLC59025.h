/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_TLC59025_H
#define __SPI_TLC59025_H

/* Platform config -----------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "string.h"

#include "stm32f0xx.h"

/* Define config -------------------------------------------------------------*/

#define TLC59025_SPI									SPI1
#define TLC59025_RCC_APB2Periph						RCC_APB2Periph_SPI1

#define TLC59025_SCK_PIN             				GPIO_Pin_3     		
#define TLC59025_SCK_GPIO_PORT      				GPIOB      	
#define TLC59025_SCK_GPIO_CLK        				RCC_AHBPeriph_GPIOB     	
#define TLC59025_SCK_SOURCE         				GPIO_PinSource3      	
#define TLC59025_SCK_AF              				GPIO_AF_0     		

#define TLC59025_MISO_PIN           				GPIO_Pin_4      		
#define TLC59025_MISO_GPIO_PORT    				GPIOB       	
#define TLC59025_MISO_GPIO_CLK      				RCC_AHBPeriph_GPIOB      	
#define TLC59025_MISO_SOURCE        				GPIO_PinSource4      	
#define TLC59025_MISO_AF            				GPIO_AF_0     		

#define TLC59025_MOSI_PIN           				GPIO_Pin_5      		
#define TLC59025_MOSI_GPIO_PORT     				GPIOB       		
#define TLC59025_MOSI_GPIO_CLK      				RCC_AHBPeriph_GPIOB      	
#define TLC59025_MOSI_SOURCE        				GPIO_PinSource5       	
#define TLC59025_MOSI_AF             				GPIO_AF_0 

#define TLC59025_NCS_LE_PIN           				GPIO_Pin_15      		
#define TLC59025_NCS_LE_GPIO_PORT     				GPIOA       		
#define TLC59025_NCS_LE_GPIO_CLK      				RCC_AHBPeriph_GPIOA

#define TLC59025_OE_PIN           					GPIO_Pin_6      		
#define TLC59025_OE_GPIO_PORT     					GPIOB       		
#define TLC59025_OE_GPIO_CLK      					RCC_AHBPeriph_GPIOB    

#define TLC59025_NCS_LE_LOW()       				GPIO_ResetBits(TLC59025_NCS_LE_GPIO_PORT, TLC59025_NCS_LE_PIN)
#define TLC59025_NCS_LE_HIGH()      				GPIO_SetBits(TLC59025_NCS_LE_GPIO_PORT, TLC59025_NCS_LE_PIN) 

#define TLC59025_OE_LOW()       					GPIO_ResetBits(TLC59025_OE_GPIO_PORT, TLC59025_OE_PIN)
#define TLC59025_OE_HIGH()      					GPIO_SetBits(TLC59025_OE_GPIO_PORT, TLC59025_OE_PIN) 

/* Macro ---------------------------------------------------------------------*/
/*

OUT	 	 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
LED   		B3 G2 R2 B2 G1 R1 B1 G5 R5 B5 G4 R4 B4 G3 R3

*/

enum
{
	OUT0 = 0x00,
	OUT1 ,
	OUT2 ,
	OUT3 ,
	OUT4 ,
	OUT5 ,

	OUT6 ,
	OUT7 ,
	OUT8 ,
	OUT9 ,
	OUT10 ,	

	OUT11 ,
	OUT12 ,
	OUT13 ,
	OUT14 ,
	OUT15 ,		
};

#define R1			(uint16_t)(1<<OUT9)
#define G1			(uint16_t)(1<<OUT10)
#define B1			(uint16_t)(1<<OUT8)

#define R2			(uint16_t)(1<<OUT12)
#define G2			(uint16_t)(1<<OUT13)
#define B2			(uint16_t)(1<<OUT11)

#define R3			(uint16_t)(1<<OUT0)
#define G3			(uint16_t)(1<<OUT1)
#define B3			(uint16_t)(1<<OUT14)

#define R4			(uint16_t)(1<<OUT3)
#define G4			(uint16_t)(1<<OUT4)
#define B4			(uint16_t)(1<<OUT2)

#define R5			(uint16_t)(1<<OUT6)
#define G5			(uint16_t)(1<<OUT7)
#define B5			(uint16_t)(1<<OUT5)

#define R1_OFF		(uint16_t)(0<<OUT9)
#define G1_OFF		(uint16_t)(0<<OUT10)
#define B1_OFF		(uint16_t)(0<<OUT8)
#define R2_OFF		(uint16_t)(0<<OUT12)
#define G2_OFF		(uint16_t)(0<<OUT13)
#define B2_OFF		(uint16_t)(0<<OUT11)
#define R3_OFF		(uint16_t)(0<<OUT0)
#define G3_OFF		(uint16_t)(0<<OUT1)
#define B3_OFF		(uint16_t)(0<<OUT14)
#define R4_OFF		(uint16_t)(0<<OUT3)
#define G4_OFF		(uint16_t)(0<<OUT4)
#define B4_OFF		(uint16_t)(0<<OUT2)
#define R5_OFF		(uint16_t)(0<<OUT6)
#define G5_OFF		(uint16_t)(0<<OUT7)
#define B5_OFF		(uint16_t)(0<<OUT5)

#define ALL			(R1|R2|R3|R4|R5|G1|G2|G3|G4|G5|B1|B2|B3|B4|B5)
#define NONE		(0x0000)
/* Exported types ------------------------------------------------------------*/

void createTLC59025Example(void);
void sendDataTLC59025(uint16_t Data);
void writeByteTLC59025(uint8_t Data);
void configTLC59025(void);

/* Exported constants --------------------------------------------------------*/

#endif  /* __SPI_TLC59025_H */

