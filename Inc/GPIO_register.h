/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	Nada Alaa			************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	GPIO			    ************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef GPIO_REGISTER_H_
#define GPIO_REGISTER_H_

#include "STD_TYPES.h"

/*GPIO registers*/
typedef struct {
	volatile u32 MODER;			//GPIO port mode register
	volatile u32 OTYPER;		//GPIO port output type register
	volatile u32 OSPEEDR;		//GPIO port output speed register
	volatile u32 PUPDR;			//GPIO port pull-up/pull-down register
	volatile u32 IDR;			//GPIO port input data register
	volatile u32 ODR;			//GPIO port output data register
	volatile u32 BSRR;			//GPIO port bit set/reset register
	volatile u32 LCKR;			//GPIO port configuration lock register
	volatile u32 AFRL;			//GPIO alternate function low register
	volatile u32 AFRH;			//GPIO alternate function high register
}GPIO_t;


/*base Addresses*/
#define GPIOA  ((volatile GPIO_t*)0x40020000)         //16 pins

#define GPIOB  ((volatile GPIO_t*)0x40020400)	      //16 pins

#define GPIOC  ((volatile GPIO_t*)0x40020800)		  //16 pins

#define GPIOD  ((volatile GPIO_t*)0x40020C00)		 //1 pins

#define GPIOH  ((volatile GPIO_t*)0x40021C00)		 //2 pins


#endif /* GPIO_REGISTER_H_ */
