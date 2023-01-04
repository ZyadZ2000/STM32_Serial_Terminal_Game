/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM				************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	RCC					************************/
/********************			Version	:	2.00				************************/
/***************************************************************************************/
/***************************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_private.h"
#include "RCC_interface.h"
#include "RCC_register.h"
#include "RCC_config.h"



/* Set Clock Frequency For Processor & Buses */
void MCAL_RCC_voidIntiSysClock(void)
{
	#if INITIAL_SYS_CLK == RCC_HSI
	
		/* Disable HSI to Set Configuration */
		CLR_BIT(RCC_CR , RCC_CR_HSION);
		
		/* Set Trimming Value to 0 */
		SET_BIT(RCC_CR , RCC_CR_HSITRIM4);
		
		/* SET HSI as a System CLK */
		CLR_BIT(RCC_CFGR , RCC_CFGR_SW0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
		
		/* Enable HSI */
		SET_BIT(RCC_CR , RCC_CR_HSION);

		/* Polling (busy Waiting) until HSI is Ready */
		while (!GET_BIT(RCC_CR , RCC_CR_HSIRDY));

		/* Polling (busy Waiting) until HSI is chosen as System CLK */
		while (GET_BIT(RCC_CFGR , RCC_CFGR_SWS0));
		while (GET_BIT(RCC_CFGR , RCC_CFGR_SWS1));
	
	#elif INITIAL_SYS_CLK == RCC_HSE_CRYSTAL
		
		/* Disable HSE to Set Configuration */
		CLR_BIT(RCC_CR , RCC_CR_HSEON);

		/* Disable HSE BYPASS */
		CLR_BIT(RCC_CR , RCC_CR_HSEBYP);
	
		/* SET HSE as a System CLK */
		SET_BIT(RCC_CFGR , RCC_CFGR_SW0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
		
		/* Enable HSE */
		SET_BIT(RCC_CR , RCC_CR_HSEON);

		/* Polling (busy Waiting) until HSE is Ready */
		while (!GET_BIT(RCC_CR , RCC_CR_HSERDY));

		/* Polling (busy Waiting) until HSE is chosen as System CLK */
		while (!GET_BIT(RCC_CFGR , RCC_CFGR_SWS0));
		while ( GET_BIT(RCC_CFGR , RCC_CFGR_SWS1));

	#elif INITIAL_SYS_CLK == RCC_HSE_RC
	
		/* Disable HSE to Set Configuration */
		CLR_BIT(RCC_CR , RCC_CR_HSEON);
		
		/* Enable HSE BYPASS */
		SET_BIT(RCC_CR , RCC_CR_HSEBYP);
		
		/* SET HSE as a System CLK */
		SET_BIT(RCC_CFGR , RCC_CFGR_SW0);
		CLR_BIT(RCC_CFGR , RCC_CFGR_SW1);
		
		/* Enable HSE */
		SET_BIT(RCC_CR , RCC_CR_HSEON);

		/* Polling (busy Waiting) until HSE is Ready */
		while (!GET_BIT(RCC_CR , RCC_CR_HSERDY));

		/* Polling (busy Waiting) until HSE is chosen as System CLK */
		while (!GET_BIT(RCC_CFGR , RCC_CFGR_SWS0));
		while ( GET_BIT(RCC_CFGR , RCC_CFGR_SWS1));
		
		
		
	#elif INITIAL_SYS_CLK == RCC_PLL
	
		/* Disable PLL */
		CLR_BIT(RCC_CR , RCC_CR_PLLON);
	
		#if 	PLL_INPUT_SRC == PLL_HSE_SRC
		
			/* Enable HSE */
			SET_BIT(RCC_CR , RCC_CR_HSEON);

			/* Polling (busy Waiting) until HSE is Ready */
			while (!GET_BIT(RCC_CR , RCC_CR_HSERDY));

			/* Select HSE as PLL Input CLK */
			SET_BIT(RCC_PLL_CFGR , RCC_PLLCFGR_PLLSRC);
			
		#elif	PLL_INPUT_SRC == PLL_HSI_SRC
			
			/* Enable HSI */
			SET_BIT(RCC_CR , RCC_CR_HSION);

			/* Polling (busy Waiting) until HSI is Ready */
			while (!GET_BIT(RCC_CR , RCC_CR_HSIRDY));

			/* Select HSI as PLL Input CLK */
			CLR_BIT(RCC_PLL_CFGR , RCC_PLLCFGR_PLLSRC);
			
		#else
			#error "Wrong PLL Input Source Choice "
		#endif
		
		/* PLL Multiplication & Division Factors Mask */
		RCC_PLL_CFGR &= PLL_MUL_MASK
		
		/* Set PLLP Division &  Multiplication Factors For PLLP, PLLM, PLLN */
		RCC_PLL_CFGR |= PLLP_DIV_FACTOR;
		RCC_PLL_CFGR |= PLLM_DIV_FACTOR;
		RCC_PLL_CFGR |= PLLN_MUL_FACTOR;

		
		/* SET PLL as a System CLK */
		CLR_BIT(RCC_CFGR , RCC_CFGR_SW0);
		SET_BIT(RCC_CFGR , RCC_CFGR_SW1);
		
		/* Enable PLL */
		SET_BIT(RCC_CR , RCC_CR_PLLON);
		
		/* Polling (busy Waiting) until PLL is Ready */
		while (!GET_BIT(RCC_CR , RCC_CR_PLLRDY));
		
		/* Polling (busy Waiting) until PLL is chosen as System CLK */
		while ( GET_BIT(RCC_CFGR , RCC_CFGR_SWS0));
		while (!GET_BIT(RCC_CFGR , RCC_CFGR_SWS1));
	
	#else
		#error " Wrong Clock System Type Choice "
	#endif
	
	/* Configure Clock Security System */
	#if CLK_SECURITY_SYS == ENABLE_CLK_SECURITY_SYS

		/* Enable Clock Security System */
		SET_BIT(RCC_CR , RCC_CR_CSSON);

	#elif CLK_SECURITY_SYS == DISABLE_CLK_SECURITY_SYS

		/* Enable Clock Security System */
		CLR_BIT(RCC_CR , RCC_CR_CSSON);

	#else
		#warning " Wrong Clock Security System Configuration Choice "
	#endif
	
	/* Buses Prescaler Mask */
	RCC_CFGR &= BUS_PRESCALER_MASK;
	
	/* SET Division Factors For AHB, APB1, APB2 Buses */
	RCC_CFGR |= AHB_CLK_DIV_FACTOR;
	RCC_CFGR |= APB1_CLK_DIV_FACTOR;
	RCC_CFGR |= APB2_CLK_DIV_FACTOR;
}


/* Description : A function to Enable Clock on Peripheral */
u8 MCAL_RCC_voidEnablePeripheralClock(u8 Copy_u8BusId , u8 Copy_u8peripheralId)
{
	/* Error state OK */
	u8 Local_u8ErrorState = OK;
	
	/* Check Peripheral number don't exceed 31 */
	if(Copy_u8peripheralId <= REGISTER_LIMIT)
	{
		/* Enable Peripheral on specific Bus */
		switch (Copy_u8BusId)
		{
		#if RCC_POWER_MODE == NORMAL_POWER_MODE
		
			case RCC_AHB1	:	SET_BIT(RCC_AHB1_ENR,Copy_u8peripheralId);		break;		//AHB1
			case RCC_AHB2	:	SET_BIT(RCC_AHB2_ENR,Copy_u8peripheralId);		break;		//AHB2
			case RCC_AHB3	:	SET_BIT(RCC_AHB3_ENR,Copy_u8peripheralId);		break;		//AHB3
			case RCC_APB1	:	SET_BIT(RCC_APB1_ENR,Copy_u8peripheralId);		break;		//APB1
			case RCC_APB2	:	SET_BIT(RCC_APB2_ENR,Copy_u8peripheralId);		break;		//APB2
			default 		:	Local_u8ErrorState = NOK;						break;		//Error State NOT OK
			
		#elif RCC_POWER_MODE == LOW_POWER_MODE
		
			case RCC_AHB1	:	SET_BIT(RCC_AHB1_LPENR,Copy_u8peripheralId);	break;		//AHB1
			case RCC_AHB2	:	SET_BIT(RCC_AHB2_LPENR,Copy_u8peripheralId);	break;		//AHB2
			case RCC_AHB3	:	SET_BIT(RCC_AHB3_LPENR,Copy_u8peripheralId);	break;		//AHB3
			case RCC_APB1	:	SET_BIT(RCC_APB1_LPENR,Copy_u8peripheralId);	break;		//APB1
			case RCC_APB2	:	SET_BIT(RCC_APB2_LPENR,Copy_u8peripheralId);	break;		//APB2
			default 		:	Local_u8ErrorState = NOK;						break;		//Error State NOT OK
			
		#else 
			#error("Please Select a Suitable Power Mode")
		#endif
		}
	}
	else 
	{
		/* Error State NOT OK */
		Local_u8ErrorState = NOK;
	}
	
	/* Return Error State */
	return Local_u8ErrorState;
}


/* Description : A function to Disable Clock on Peripheral */
u8 MCAL_RCC_voidDisablePeripheralClock(u8 Copy_u8BusId , u8 Copy_u8peripheralId)
{
	/* Error state OK */
	u8 Local_u8ErrorState = OK;
	
	/* Check Peripheral number don't exceed 31 */
	if(Copy_u8peripheralId <= REGISTER_LIMIT)
	{
		/* Disable Peripheral on specific Bus */
		switch (Copy_u8BusId)
		{
		#if RCC_POWER_MODE == NORMAL_POWER_MODE
		
			case RCC_AHB1	:	CLR_BIT(RCC_AHB1_ENR,Copy_u8peripheralId);		break;		//AHB1
			case RCC_AHB2	:	CLR_BIT(RCC_AHB2_ENR,Copy_u8peripheralId);		break;		//AHB2
			case RCC_AHB3	:	CLR_BIT(RCC_AHB3_ENR,Copy_u8peripheralId);		break;		//AHB3
			case RCC_APB1	:	CLR_BIT(RCC_APB1_ENR,Copy_u8peripheralId);		break;		//APB1
			case RCC_APB2	:	CLR_BIT(RCC_APB2_ENR,Copy_u8peripheralId);		break;		//APB2
			default 		:	Local_u8ErrorState = NOK;						break;		//Error State NOT OK
			
		#elif RCC_POWER_MODE == LOW_POWER_MODE
		
			case RCC_AHB1	:	CLR_BIT(RCC_AHB1_LPENR,Copy_u8peripheralId);	break;		//AHB1
			case RCC_AHB2	:	CLR_BIT(RCC_AHB2_LPENR,Copy_u8peripheralId);	break;		//AHB2
			case RCC_AHB3	:	CLR_BIT(RCC_AHB3_LPENR,Copy_u8peripheralId);	break;		//AHB3
			case RCC_APB1	:	CLR_BIT(RCC_APB1_LPENR,Copy_u8peripheralId);	break;		//APB1
			case RCC_APB2	:	CLR_BIT(RCC_APB2_LPENR,Copy_u8peripheralId);	break;		//APB2
			default 		:	Local_u8ErrorState = NOK;						break;		//Error State NOT OK
			
		#else 
			#error("Please Select a Suitable Power Mode")
		#endif
		}
	}
	else 
	{
		/* Error State NOT OK */
		Local_u8ErrorState = NOK;
	}
	
	/* Return Error State */
	return Local_u8ErrorState;
}




