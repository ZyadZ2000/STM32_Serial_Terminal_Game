/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM				************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	RCC					************************/
/********************			Version	:	2.00				************************/
/***************************************************************************************/
/***************************************************************************************/



#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/********************************************************************************************/
/*							SELECT Power Mode for Peripherals Clock:						*/
/*																							*/
/*		Options :						0-NORMAL_POWER_MODE									*/
/*										1-LOW_POWER_MODE									*/
/*																							*/
/********************************************************************************************/

#define RCC_POWER_MODE					NORMAL_POWER_MODE



/********************************************************************************************/
/*									SELECT Initial System CLK :								*/
/*																							*/
/*		Options :						0-RCC_HSI											*/
/*										1-RCC_HSE_CRYSTAL									*/
/*										2-RCC_HSE_RC										*/
/*										3-RCC_PLL											*/
/*																							*/
/********************************************************************************************/

#define INITIAL_SYS_CLK					RCC_HSI



#if INITIAL_SYS_CLK == RCC_PLL

/********************************************************************************************/
/*									SELECT PLL Input Source									*/
/*																							*/
/*		Options :						0-PLL_HSI_SRC										*/
/*										1-PLL_HSE_SRC										*/
/*																							*/
/********************************************************************************************/

#define PLL_INPUT_SRC					PLL_HSE_SRC


/********************************************************************************************/
/*		SELECT PLLP According => f(PLL general clock output) = f(VCO Output clock) / PLLP:	*/
/*																							*/
/*		Options :						0-PLLP_2											*/
/*										1-PLLP_4											*/
/*										2-PLLP_6											*/
/*										3-PLLP_8											*/
/*																							*/
/*		Caution : The software has to set these bits correctly not to exceed 180 MHz		*/
/*		Caution :	f(VCO Output clock) shall be between (100 MHz - 432 MHz)				*/
/*																							*/
/********************************************************************************************/

#define PLLP_DIV_FACTOR					PLLP_2


/********************************************************************************************/
/*		SELECT PLLM According => f(VCO Input clock) = f(PLL Input clock) / PLLM:			*/
/*																							*/
/*		Options :					2 ≤ PLLM ≤ 63											*/
/*																							*/
/*		Caution : The software has to set these bits correctly to ensure that the 			*/
/*			f(VCO Input clock) ranges from 1 to 2 MHz. It is recommended to 				*/
/*				select a frequency 	of 2 MHz to limit PLL jitter							*/
/*																							*/
/*		Caution : f(PLL clock input) is HSI or HSE CLK frequency							*/			
/*																							*/
/********************************************************************************************/

#define PLLM_DIV_FACTOR					4


/********************************************************************************************/
/*		SELECT PLLN According => f(VCO Output clock) = f(VCO Input clock) × PLLN:			*/
/*																							*/
/*		Options :					50 ≤ PLLN ≤ 432											*/
/*																							*/
/*		Caution :	f(VCO Output clock) shall be between (100 MHz - 432 MHz)				*/
/*																							*/
/********************************************************************************************/

#define PLLN_MUL_FACTOR					180

#endif



/********************************************************************************************/
/*								SELECT AHB Prescaler :										*/
/*																							*/
/*		Options :				0-SYS_CLK_NOT_DIV											*/
/*								1-SYS_CLK_DIV_BY_2											*/
/*								2-SYS_CLK_DIV_BY_4											*/
/*								3-SYS_CLK_DIV_BY_8											*/
/*								4-SYS_CLK_DIV_BY_16											*/
/*								5-SYS_CLK_DIV_BY_64											*/
/*								6-SYS_CLK_DIV_BY_128										*/
/*								7-SYS_CLK_DIV_BY_256										*/
/*								8-SYS_CLK_DIV_BY_512										*/
/*																							*/
/********************************************************************************************/

#define AHB_CLK_DIV_FACTOR				SYS_CLK_NOT_DIV



/********************************************************************************************/
/*								SELECT APB1 Prescaler :										*/
/*																							*/
/*		Options :				0-APB1_AHB_CLK_NOT_DIV										*/
/*								1-APB1_AHB_CLK_DIV_BY_2										*/
/*								2-APB1_AHB_CLK_DIV_BY_4										*/
/*								3-APB1_AHB_CLK_DIV_BY_8										*/
/*								4-APB1_AHB_CLK_DIV_BY_16									*/
/*																							*/
/*		Caution : The software has to set these bits correctly not to exceed 45 MHz			*/
/*																							*/
/********************************************************************************************/

#define APB1_CLK_DIV_FACTOR				APB1_AHB_CLK_NOT_DIV



/********************************************************************************************/
/*								SELECT APB2 Prescaler :										*/
/*																							*/
/*		Options :				0-APB2_AHB_CLK_NOT_DIV										*/
/*								1-APB2_AHB_CLK_DIV_BY_2										*/
/*								2-APB2_AHB_CLK_DIV_BY_4										*/
/*								3-APB2_AHB_CLK_DIV_BY_8										*/
/*								4-APB2_AHB_CLK_DIV_BY_16									*/
/*																							*/
/*		Caution : The software has to set these bits correctly not to exceed 90 MHz			*/
/*																							*/
/********************************************************************************************/

#define APB2_CLK_DIV_FACTOR				APB2_AHB_CLK_NOT_DIV



/********************************************************************************************/
/*								SELECT CLOCK_SECURITY_SYSTEM								*/
/*																							*/
/*		Options :				0-ENABLE_CLK_SECURITY_SYS									*/
/*								1-DISABLE_CLK_SECURITY_SYS									*/
/*																							*/
/********************************************************************************************/

#define CLK_SECURITY_SYS				DISABLE_CLK_SECURITY_SYS



#endif


