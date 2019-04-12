/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    24-July-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "Hw_config.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t LED1_Hex = 0xFFFFFF;
uint32_t LED2_Hex = 0xFFFFFF;
uint32_t LED3_Hex = 0xFFFFFF;
uint32_t LED4_Hex = 0xFFFFFF;
uint32_t LED5_Hex = 0xFFFFFF;

uint16_t TableIndex = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();

}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	
		if (!UartRxFlag)
		{
			UartRxBuffer = USART_ReceiveData(USART1);
			printf("temp = 0x%x \n\r",UartRxBuffer);		
			UartRxFlag = 1;
		}
	}
}

void TIM17_IRQHandler(void)
{
	static uint16_t LED5_Cnt = 0;
	static uint16_t LED4_Cnt = 0;	
	static uint8_t LED4_Flag = 1;	
	static uint16_t LED3_Cnt = 0;
	static uint16_t LED2_Cnt = 0;
	static uint8_t LED2_Flag = 1;
	static uint16_t LED1_Cnt = 0;
	static uint8_t LED1_Flag = 1;
	
	if (TIM_GetITStatus(TIM17, TIM_IT_Update) != RESET)
	{
		
		if (LED1_Cnt++ >=1000)
		{
			if (LED1_Flag)
			{
				LED1_Flag = 0;
				LED1_Hex = 0x00FFFF;
			}
			else
			{
				LED1_Flag = 1;
				LED1_Hex = 0x000000;				
			}			
			LED1_Cnt = 0;
		}

		if (LED2_Cnt++ >=1000)
		{
			if (LED2_Flag)
			{
				LED2_Flag = 0;
				LED2_Hex = 0x00FF00;
			}
			else
			{
				LED2_Flag = 1;
				LED2_Hex = 0x0000FF;				
			}			
			LED2_Cnt = 0;
		}
		
		if (LED3_Cnt++ >=1)
		{
			if (LED3_Hex-- == 0)
			{
				LED3_Hex = 0xFFFFFF;
			}
			LED3_Cnt = 0;
		}

		if (LED4_Cnt++ >=500)
		{	
			if (LED4_Flag)
			{
				LED4_Flag = 0;
				LED4_Hex = 0xFFEE00;
			}
			else
			{
				LED4_Flag = 1;
				LED4_Hex = 0xD000FF;				
			}			
			LED4_Cnt = 0;
		}
		
		if (LED5_Cnt++ >=60)
		{	
			if((TableIndex++) >= (300-1)) 
			{
				TableIndex = 0;
			}
			LED5_Hex = RGBColorTable[TableIndex];

			LED5_Cnt = 0;
		}
	
		TIM_ClearITPendingBit(TIM17, TIM_IT_Update);		
	}
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
