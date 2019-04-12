/* Includes ------------------------------------------------------------------*/
#include "Custom_SPI_TLC59025.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*SPI variable*/
uint8_t sDummy=0x5A;
//uint8_t Rx_Buffer1 = 0;

extern void Delay(__IO uint32_t mTime);
static void delay(__IO uint32_t nCount)
{
    while (nCount != 0)
    {
        nCount--;
    }
}

void startTLC59025DMABuffer(uint8_t pBuffer, uint16_t NumByteToWrite)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* DMA configuration -------------------------------------------------------*/
	/* Deinitialize DMA Streams */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_DeInit(DMA1_Channel3);
//	DMA_DeInit(DMA1_Channel2);

	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = NumByteToWrite ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(TLC59025_SPI->DR)) ;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	/* Configure TX DMA */
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST ;
	DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t) &pBuffer ;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

	#if 0
	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = NumByteToWrite ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(TLC59025_SPI->DR)) ;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* Configure RX DMA */
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;
	DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)&sDummy ; 
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	#endif

	/* Enable DMA SPI TX Stream */
	DMA_Cmd(DMA1_Channel3,ENABLE);
	/* Enable DMA SPI RX Stream */
//	DMA_Cmd(DMA1_Channel2,ENABLE);
	/* Enable SPI DMA TX Requsts */
	SPI_I2S_DMACmd(TLC59025_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
	/* Enable SPI DMA RX Requsts */
//	SPI_I2S_DMACmd(TLC59025_SPI, SPI_I2S_DMAReq_Rx, ENABLE);
	/* The Data transfer is performed in the SPI using Direct Memory Access */

}

void waitTLC59025DMABuffer(void)
{
	/* Waiting the end of Data transfer */
	while (DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);
//	while (DMA_GetFlagStatus(DMA1_FLAG_TC2)==RESET);
	
	/* Clear DMA Transfer Complete Flags */
	DMA_ClearFlag(DMA1_FLAG_GL3);//DMA1_FLAG_TC3
//	DMA_ClearFlag(DMA1_FLAG_GL2);//DMA1_FLAG_TC2  
	
	/* Disable DMA SPI TX Stream */
	DMA_Cmd(DMA1_Channel3,DISABLE);
	/* Disable DMA SPI RX Stream */
//	DMA_Cmd(DMA1_Channel2,DISABLE);  
	
	/* Disable SPI DMA TX Requsts */
	SPI_I2S_DMACmd(TLC59025_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
	/* Disable SPI DMA RX Requsts */
//	SPI_I2S_DMACmd(TLC59025_SPI, SPI_I2S_DMAReq_Rx, DISABLE);

}


void writeByteTLC59025(uint8_t Data)
{
#if 0
	delay(5);
	TLC59025_OE_HIGH();
	TLC59025_NCS_LE_LOW();	
	
//	startTLC59025DMABuffer(~(Data),1);
	startTLC59025DMABuffer((Data),1);
	waitTLC59025DMABuffer();	

	delay(5);	
	TLC59025_NCS_LE_HIGH();
	TLC59025_OE_LOW();
#else
	
	while (SPI_I2S_GetFlagStatus(TLC59025_SPI, SPI_I2S_FLAG_TXE) == RESET)
	{};
	SPI_SendData8(TLC59025_SPI,Data);
//	SPI_SendData8(TLC59025_SPI, ~(Data));
	
	while (SPI_I2S_GetFlagStatus(TLC59025_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{};
	SPI_ReceiveData8(TLC59025_SPI);

#endif
}

void sendDataTLC59025(uint16_t Data)
{
//	TLC59025_OE_LOW();
	TLC59025_OE_HIGH();
	delay(1);
	
//	TLC59025_NCS_LE_HIGH();
	TLC59025_NCS_LE_LOW();					
	delay(1);
	
	writeByteTLC59025(Data>>8);	
	writeByteTLC59025(Data&0xFF);
	
	TLC59025_NCS_LE_HIGH();
	delay(5);
	TLC59025_NCS_LE_LOW();
	delay(10);	
	
//	TLC59025_OE_HIGH();
	TLC59025_OE_LOW();	
	delay(1);
	
//	delay(1000);
//	TLC59025_OE_HIGH();
}

void createTLC59025Example(void)
{
#if 0
	sendDataTLC59025(R1);Delay(1000);
	sendDataTLC59025(R2);Delay(1000);
	sendDataTLC59025(R3);Delay(1000);
	sendDataTLC59025(R4);Delay(1000);
	sendDataTLC59025(R5);Delay(1000);

	sendDataTLC59025(G1);Delay(1000);
	sendDataTLC59025(G2);Delay(1000);
	sendDataTLC59025(G3);Delay(1000);
	sendDataTLC59025(G4);Delay(1000);
	sendDataTLC59025(G5);Delay(1000);

	sendDataTLC59025(B1);Delay(1000);
	sendDataTLC59025(B2);Delay(1000);
	sendDataTLC59025(B3);Delay(1000);
	sendDataTLC59025(B4);Delay(1000);
	sendDataTLC59025(B5);Delay(1000);

#endif
	
#if 0
	sendDataTLC59025(R1);
	Delay(100);
	sendDataTLC59025(R2);
	Delay(100);
	sendDataTLC59025(R3);
	Delay(100);
	sendDataTLC59025(R4);
	Delay(100);
	sendDataTLC59025(R5);
	Delay(100);
	sendDataTLC59025(R4);
	Delay(100);
	sendDataTLC59025(R3);
	Delay(100);
	sendDataTLC59025(R2);
	Delay(100);
	sendDataTLC59025(R1);
	Delay(100);	

	sendDataTLC59025(G1);
	Delay(100);
	sendDataTLC59025(G2);
	Delay(100);
	sendDataTLC59025(G3);
	Delay(100);
	sendDataTLC59025(G4);
	Delay(100);
	sendDataTLC59025(G5);
	Delay(100);
	sendDataTLC59025(G4);
	Delay(100);
	sendDataTLC59025(G3);
	Delay(100);
	sendDataTLC59025(G2);
	Delay(100);
	sendDataTLC59025(G1);
	Delay(100);
	
	sendDataTLC59025(B1);
	Delay(100);
	sendDataTLC59025(B2);
	Delay(100);
	sendDataTLC59025(B3);
	Delay(100);
	sendDataTLC59025(B4);
	Delay(100);
	sendDataTLC59025(B5);
	Delay(100);
	sendDataTLC59025(B4);
	Delay(100);
	sendDataTLC59025(B3);
	Delay(100);
	sendDataTLC59025(B2);
	Delay(100);
	sendDataTLC59025(B1);
	Delay(100);	

	sendDataTLC59025(ALL);
	Delay(1000);		
	sendDataTLC59025(NONE);
	Delay(1000);
	sendDataTLC59025(ALL);
	Delay(1000);		
	sendDataTLC59025(NONE);
	Delay(1000);
	
#endif

#if 1
	sendDataTLC59025(R1|R2|R3|R4|R5);
	Delay(1000);

	sendDataTLC59025(G1|G2|G3|G4|G5);
	Delay(1000);

	sendDataTLC59025(B1|B2|B3|B4|B5);
	Delay(1000);
#endif

#if 0
	sendDataTLC59025(ALL);
	Delay(1000);
	sendDataTLC59025(0x7F7F);
	Delay(1000);
	sendDataTLC59025(0x3F3F);
	Delay(1000);
	sendDataTLC59025(NONE);
	Delay(1000);
#endif
	
#if 0
	static uint16_t i = 0;

	sendDataTLC59025(i++);
	Delay(10);
	if (i>=0xFFFF)
	{
		i = 0;
	}	
#endif
}

/*====================================================================
PCB					TLC59025							MCU
----------------------------------------------------------------------			
*			MR#   : master reset (active LOW)			=>VCC
SCLOCK		SHCP  : shift register clock input			=>TLC59025_SPI_CLK , PA5
LATCH		STCP  : storage register clock input			=>TLC59025_SPI_NSS , PA8
DIN			DS    : serial data input					=>TLC59025_SPI_MOSI , PA7(NA)
SDO			DS    : serial data out					=>TLC59025_SPI_MISO , PA6

====================================================================*/

void configTLC59025(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	/* Enable the SPI periph */
	RCC_APB2PeriphClockCmd(TLC59025_RCC_APB2Periph, ENABLE);

	/* Enable SCK, MOSI, MISO and NSS GPIO clocks */
	RCC_AHBPeriphClockCmd(TLC59025_SCK_GPIO_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(TLC59025_NCS_LE_GPIO_CLK, ENABLE);

	GPIO_PinAFConfig(TLC59025_SCK_GPIO_PORT,TLC59025_SCK_SOURCE,TLC59025_SCK_AF);	
	GPIO_PinAFConfig(TLC59025_MOSI_GPIO_PORT,TLC59025_MOSI_SOURCE,TLC59025_MOSI_AF);
	GPIO_PinAFConfig(TLC59025_MISO_GPIO_PORT,TLC59025_MISO_SOURCE,TLC59025_MISO_AF);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = TLC59025_SCK_PIN;
	GPIO_Init(TLC59025_SCK_GPIO_PORT, &GPIO_InitStructure);

	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  TLC59025_MOSI_PIN;
	GPIO_Init(TLC59025_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/* SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = TLC59025_MISO_PIN;
	GPIO_Init(TLC59025_MISO_GPIO_PORT, &GPIO_InitStructure);

	//NSS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = TLC59025_NCS_LE_PIN;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(TLC59025_NCS_LE_GPIO_PORT, &GPIO_InitStructure);	

	TLC59025_NCS_LE_LOW();

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = TLC59025_OE_PIN;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(TLC59025_OE_GPIO_PORT, &GPIO_InitStructure);		

	TLC59025_OE_HIGH();
	
	/* SPI configuration -------------------------------------------------------*/
	SPI_I2S_DeInit(TLC59025_SPI);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(TLC59025_SPI, &SPI_InitStructure);

	/* Initialize the FIFO threshold */
	SPI_RxFIFOThresholdConfig(TLC59025_SPI, SPI_RxFIFOThreshold_QF);

	/* Enable the SPI peripheral */
	SPI_Cmd(TLC59025_SPI, ENABLE);

}


