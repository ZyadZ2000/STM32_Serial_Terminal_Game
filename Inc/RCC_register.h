/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM				************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	RCC					************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/



#ifndef RCC_REGISTER_H_
#define RCC_REGISTER_H_


#define RCC_CR								*((volatile u32*)0x40023800)	// RCC Clock Control Register
#define RCC_PLL_CFGR						*((volatile u32*)0x40023804)	// RCC Clock PLL configuration Register
#define RCC_CFGR							*((volatile u32*)0x40023808)	// RCC Clock configuration Register 
#define RCC_CIR								*((volatile u32*)0x4002380C)	// RCC Clock Interrupt Register

#define RCC_AHB1_RSTR						*((volatile u32*)0x40023810)	// RCC AHB1 peripheral Clock Reset Register
#define RCC_AHB2_RSTR						*((volatile u32*)0x40023814)	// RCC AHB2 peripheral Clock Reset Register
#define RCC_AHB3_RSTR						*((volatile u32*)0x40023818)	// RCC AHB3 peripheral Clock Reset Register
#define RCC_APB1_RSTR						*((volatile u32*)0x40023820)	// RCC APB1 peripheral Clock Reset Register
#define RCC_APB2_RSTR						*((volatile u32*)0x40023824)	// RCC APB2 peripheral Clock Reset Register

#define RCC_AHB1_ENR						*((volatile u32*)0x40023830)	// RCC AHB1 peripheral Clock Enable Register
#define RCC_AHB2_ENR						*((volatile u32*)0x40023834)	// RCC AHB2 peripheral Clock Enable Register
#define RCC_AHB3_ENR						*((volatile u32*)0x40023838)	// RCC AHB3 peripheral Clock Enable Register
#define RCC_APB1_ENR						*((volatile u32*)0x40023840)	// RCC APB1 peripheral Clock Enable Register
#define RCC_APB2_ENR						*((volatile u32*)0x40023844)	// RCC APB2 peripheral Clock Enable Register

#define RCC_AHB1_LPENR						*((volatile u32*)0x40023850)	// RCC AHB1 peripheral Clock Enable (Low Power Mode) Register
#define RCC_AHB2_LPENR						*((volatile u32*)0x40023854)	// RCC AHB2 peripheral Clock Enable (Low Power Mode) Register
#define RCC_AHB3_LPENR						*((volatile u32*)0x40023858)	// RCC AHB3 peripheral Clock Enable (Low Power Mode) Register
#define RCC_APB1_LPENR						*((volatile u32*)0x40023860)	// RCC APB1 peripheral Clock Enable (Low Power Mode) Register
#define RCC_APB2_LPENR						*((volatile u32*)0x40023864)	// RCC APB2 peripheral Clock Enable (Low Power Mode) Register

#define RCC_BDCR							*((volatile u32*)0x40023870)	// RCC Backup Domain Control Register
#define RCC_CSR								*((volatile u32*)0x40023874)	// RCC Control Status Register
#define RCC_SSCGR							*((volatile u32*)0x40023880)	// RCC Spread Spectrum Clock Generation Register
#define RCC_PLLI2S_SCFGR					*((volatile u32*)0x40023884)	// RCC PLLI2S Configuration Register
#define RCC_PLL_SAICFGR						*((volatile u32*)0x40023888)	// RCC PLL Configuration Register
#define RCC_DCKCFGR							*((volatile u32*)0x4002388C)	// RCC Dedicated Clocks Configuration Register
#define RCC_CKGATENR						*((volatile u32*)0x40023890)	// RCC Clocks Gated Enable Register
#define RCC_DCK_CFGR2						*((volatile u32*)0x40023894)	// RCC Dedicated Clocks Configuration Register 2


#endif
