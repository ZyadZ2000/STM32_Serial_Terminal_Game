/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM      		************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	UART			    ************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#include "STD_TYPES.h"

/* UART Addresses */
#define USART1 ((volatile UART*) 0x40011000)
#define USART2 ((volatile UART*)  0x40004400)
#define USART3 ((volatile UART*)  0x40004800)
#define UART4 ((volatile UART*)  0x40004C00)
#define UART5 ((volatile UART*)  0x40005000)
#define USART6 ((volatile UART*)  0x40011400)

typedef struct {
	volatile u32 SR; // UART Status Register
	volatile u32 DR; // UART Data Register
	volatile u32 BRR; // UART Baud-Rate Register
	volatile u32 CR1; // UART Contorl Registers
	volatile u32 CR2; // UART Contorl Registers
	volatile u32 CR3; // UART Contorl Registers
	volatile u32 GTPR;
} UART;

#endif /* UART_REGISTER_H_ */
