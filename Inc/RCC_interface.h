/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM				************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	RCC					************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/



#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


/* define BUS Type */
#define RCC_AHB1							0
#define RCC_AHB2							1
#define RCC_AHB3							2
#define RCC_APB1							3
#define RCC_APB2							4


/* define AHB3 Peripherals */
#define AHB3_FMC							0
#define AHB3_QUADSPI						1


/* define AHB2 Peripherals */
#define AHB2_DCMI							0
#define AHB2_OTGFS							7


/* define AHB1 Peripherals */
#define AHB1_GPIOA							0
#define AHB1_GPIOB							1
#define AHB1_GPIOC							2
#define AHB1_GPIOD							3
#define AHB1_GPIOE							4
#define AHB1_GPIOF							5
#define AHB1_GPIOG							6
#define AHB1_GPIOH							7
#define AHB1_CRC							12
#define AHB1_BKPSRAM						18
#define AHB1_DMA1							21
#define AHB1_DMA2							22
#define AHB1_OTGHS							29
#define AHB1_OTGHSULPI						30


/* define APB2 Peripherals */
#define APB2_TIM1							0
#define APB2_TIM8							1
#define APB2_USART1							4
#define APB2_USART6							5
#define APB2_ADC1							8
#define APB2_ADC2							9
#define APB2_ADC3							10
#define APB2_SDIO							11
#define APB2_SPI1							12
#define APB2_SPI4							13
#define APB2_SYSCFG							14
#define APB2_TIM9							16
#define APB2_TIM10							17
#define APB2_TIM11							18
#define APB2_SAI1							22
#define APB2_SAI2							23


/* define APB1 Peripherals */
#define APB1_TIM2							0
#define APB1_TIM3							1
#define APB1_TIM4							2
#define APB1_TIM5							3
#define APB1_TIM6							4
#define APB1_TIM7							5
#define APB1_TIM12							6
#define APB1_TIM13							7
#define APB1_TIM14							8
#define APB1_WWDG							11
#define APB1_SPI2							14
#define APB1_SPI3							15
#define APB1_SPDIFRX						16
#define APB1_USART2							17
#define APB1_USART3							18
#define APB1_UART4							19
#define APB1_UART5							20
#define APB1_I2C1							21
#define APB1_I2C2							22
#define APB1_I2C3							23
#define APB1_FMPI2C1						24
#define APB1_CAN1							25
#define APB1_CAN2							26
#define APB1_CEC							27
#define APB1_PWR							28
#define APB1_DAC							29


/********************************************************************************************/
/*				Fun Def	:	Set Clock Frequency For Processor & Buses						*/
/*																							*/
/*				Inputs	:	Void															*/
/*																							*/
/*				Outputs : 	Void															*/
/*																							*/
/********************************************************************************************/
void MCAL_RCC_voidIntiSysClock(void);

	
/************************************************************************************************************************/
/*	Fun Def	:	Enable or Disable Clock on Peripheral																	*/
/*																														*/
/*	Inputs	:	Copy_u8BusId 		:	RCC_AHB1	||	RCC_AHB2	||	RCC_AHB3	||	RCC_APB1	||	RCC_APB2		*/
/*				Copy_u8peripheralId	:																					*/
/*																														*/
/*				NOTE : Select these Peripherals if (RCC_AHB1) is Chosen													*/
/* 	AHB1_GPIOA	||	AHB1_GPIOB	||	AHB1_GPIOC	||	AHB1_GPIOD		||	AHB1_GPIOE	||	AHB1_GPIOF						*/
/*	AHB1_GPIOG	||	AHB1_GPIOH	||	AHB1_CRC	||	AHB1_BKPSRAM	||	AHB1_DMA1	||	AHB1_DMA2						*/
/*	AHB1_OTGHS	||	AHB1_OTGHSULPI																						*/
/*																														*/
/*				NOTE : Select these Peripherals if (RCC_AHB2) is Chosen													*/
/* 	AHB2_DCMI	||	AHB2_OTGFS																							*/
/*																														*/
/*				NOTE : Select these Peripherals if (RCC_AHB3) is Chosen													*/
/*	AHB3_FMC	||	AHB3_QUADSPI																						*/
/*																														*/
/*				NOTE : Select these Peripherals if (RCC_APB1) is Chosen													*/
/*	APB1_TIM2	||	APB1_TIM3	||	APB1_TIM4	||	APB1_TIM5	||	APB1_TIM6	||	APB1_TIM7		||	APB1_TIM12		*/
/*	APB1_TIM13	||	APB1_TIM14	||	APB1_WWDG	||	APB1_SPI2	||	APB1_SPI3	||	APB1_SPDIFRX	||	APB1_USART2		*/
/*	APB1_USART3	||	APB1_UART4	||	APB1_UART5	||	APB1_I2C1	||	APB1_I2C2	||	APB1_I2C3		||	APB1_FMPI2C1	*/
/*	APB1_CAN1	||	APB1_CAN2	||	APB1_CEC	||	APB1_PWR	||	APB1_DAC											*/
/*																														*/
/*				NOTE : Select these Peripherals if (RCC_APB2) is Chosen													*/
/*	APB2_TIM1	||	APB2_TIM8	||	APB2_USART1	||	APB2_USART6	||	APB2_ADC1	||	APB2_ADC2	||	APB2_ADC13			*/
/*	APB2_SPI1	||	APB2_SPI4	||	APB2_SYSCFG	||	APB2_TIM9	||	APB2_TIM10	||	APB2_TIM11	||	APB2_SAI1			*/
/*	APB2_SDIO	||	APB2_SAI2																							*/
/*																														*/
/*	Outputs	:	Return Error State (OK | NOK)																			*/
/*																														*/
/************************************************************************************************************************/
u8 MCAL_RCC_voidEnablePeripheralClock(u8 Copy_u8BusId , u8 Copy_u8peripheralId);

u8 MCAL_RCC_voidDisablePeripheralClock(u8 Copy_u8BusId , u8 Copy_u8peripheralId);



#endif
