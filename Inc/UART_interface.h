/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM      		************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	UART			    ************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "STD_TYPES.h"

/*   UART NUMBER      */
#define USE_USART1  1
#define USE_USART2  2
#define USE_USART3  3
#define USE_UART4   4
#define USE_UART5   5
#define USE_USART6  6

/* UART_BRR Register values for different baud-rates in both cases of oversampling */
#define OVER16_2400     0x1A05
#define OVER16_9600     0x0683
#define OVER16_19200    0x0341
#define OVER16_115200   0x008B
#define OVER16_460800   0x0023
#define OVER16_921600   0x0011

#define OVER8_2400      0x3413
#define OVER8_9600      0x0D03
#define OVER8_19200     0x0681
#define OVER8_115200    0x0113
#define OVER8_460800    0x0043
#define OVER8_921600    0x0021
#define OVER8_2000000   0x0010

typedef enum {
	STOP_1, /* One Stop Bit */
	STOP_HALF, /* 0.5 Stop Bits (smart-card mode) */
	STOP_2, /* Two Stop Bits */
	STOP_1_HALF /* 1.5 Stop Bits (smart-card mode) */
} STOP_BITS;

typedef enum {
	PARITY_DISABLED, PARITY_ENABLED
} PARITY_ENABLE;

typedef enum {
	EVEN_PARITY, ODD_PARITY
} PARITY;

/* Over-sampling mode */
typedef enum {
	OVER16, OVER8
} OVER_MODE;

typedef enum {
	EIGHT_BITS, NINE_BITS
} DATA_LENGHT;

/* UART Configuration Structure */
typedef struct {
	u8 UART_num;
	STOP_BITS stop_bits;
	PARITY_ENABLE parity_mode;
	PARITY parity_bits;
	OVER_MODE oversampling_mode;
	DATA_LENGHT data_bits;
	u32 baud_rate;
} UART_ConfigType;

/* Initialize The UART with the desired Configurations */
void MCAL_UART_init(UART_ConfigType *config_ptr);

void MCAL_UART_enableRecieveInterrupt(u8 UART_num);

void MCAL_UART_disableRecieveInterrupt(u8 UART_num);

void MCAL_UART_enableTransmitInterrupt(u8 UART_num);

void MCAL_UART_disableTransmitInterrupt(u8 UART_num);

void MCAL_UART_sendCharacter(u8 UART_num, u8 data);

void MCAL_UART_sendString(u8 UART_num, u8 *data);

u8 MCAL_UART_recieveCharacter(u8 UART_num);

void MCAL_UART_recieveString(u8 UART_Num, u8 *data);

#endif /* UART_INTERFACE_H_ */

