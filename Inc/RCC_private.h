/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM				************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	RCC					************************/
/********************			Version	:	2.00				************************/
/***************************************************************************************/
/***************************************************************************************/



#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/* define Register Limit */
#define REGISTER_LIMIT						31


/*Define Power Modes */
#define LOW_POWER_MODE						1
#define NORMAL_POWER_MODE					2


/* define Initial System Clock */
#define RCC_HSI								1
#define RCC_HSE_CRYSTAL						2
#define RCC_HSE_RC							3
#define RCC_PLL								4


/* define PLL Input Source */
#define PLL_HSI_SRC							1
#define PLL_HSE_SRC							2


/* define PLL Multiplication Mask */
#define PLL_MUL_MASK						0xFFFC8000


/* define PLLP Division Factors */
#define PLLP_2								0x00000000
#define PLLP_4								0x00010000
#define PLLP_6								0x00020000
#define PLLP_8								0x00030000


/* define Buses Prescaler Mask */
#define BUS_PRESCALER_MASK					0xFFFF030F


/* define AHB Prescaler Factors */
#define SYS_CLK_NOT_DIV						0x00000000
#define SYS_CLK_DIV_BY_2					0x00000080
#define SYS_CLK_DIV_BY_4					0x00000090
#define SYS_CLK_DIV_BY_8					0x000000A0
#define SYS_CLK_DIV_BY_16					0x000000B0
#define SYS_CLK_DIV_BY_64					0x000000C0
#define SYS_CLK_DIV_BY_128					0x000000D0
#define SYS_CLK_DIV_BY_256					0x000000E0
#define SYS_CLK_DIV_BY_512					0x000000F0


/* define APB1 Prescaler Factors */
#define APB1_AHB_CLK_NOT_DIV				0x00000000
#define APB1_AHB_CLK_DIV_BY_2				0x00001000
#define APB1_AHB_CLK_DIV_BY_4				0x00001400
#define APB1_AHB_CLK_DIV_BY_8				0x00001800
#define APB1_AHB_CLK_DIV_BY_16				0x00001C00


/* define APB2 Prescaler Factors */
#define APB2_AHB_CLK_NOT_DIV				0x00000000
#define APB2_AHB_CLK_DIV_BY_2				0x00008000
#define APB2_AHB_CLK_DIV_BY_4				0x0000A000
#define APB2_AHB_CLK_DIV_BY_8				0x0000C000
#define APB2_AHB_CLK_DIV_BY_16				0x0000E000


/* define Clock Security System */
#define ENABLE_CLK_SECURITY_SYS				1
#define DISABLE_CLK_SECURITY_SYS			2


/* define RCC Clock Control Register Bits */
#define RCC_CR_HSION						0			//HSI ENABLE
#define RCC_CR_HSIRDY						1			//HSI READY
#define RCC_CR_HSITRIM0						3			//HSI TRIM BIT 0
#define RCC_CR_HSITRIM1						4			//HSI TRIM BIT 1
#define RCC_CR_HSITRIM2						5			//HSI TRIM BIT 2
#define RCC_CR_HSITRIM3						6			//HSI TRIM BIT 3
#define RCC_CR_HSITRIM4						7			//HSI TRIM BIT 4
#define RCC_CR_HSEON						16			//HSE ENABLE
#define RCC_CR_HSERDY						17			//HSI READY
#define RCC_CR_HSEBYP						18			//HSI BYPASS
#define RCC_CR_CSSON						19			//CSS ENABLE
#define RCC_CR_PLLON						24			//PLL ENABLE
#define RCC_CR_PLLRDY						25			//PLL READY

/* define RCC Clock configuration Register Bits */
#define RCC_CFGR_SW0						0			//SYS CLK SWITCH BIT0
#define RCC_CFGR_SW1						1			//SYS CLK SWITCH BIT1
#define RCC_CFGR_SWS0						2			//SYS CLK SWITCH STATUS BIT0
#define RCC_CFGR_SWS1						3			//SYS CLK SWITCH STATUS BIT1

/* define RCC PLL configuration Register Bits */
#define RCC_PLLCFGR_PLLSRC					22			//PLL SRC

#endif

