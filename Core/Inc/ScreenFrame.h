#ifndef SCREENFRAME_H
#define SCREENFRAME_H

#include "freertos_ao.h"
#include "stm32f4xx_hal_uart.h"

typedef struct {
	Event super;
	char * frame;
	uint16_t frame_len;
}ScreenFrameEvent;

typedef struct {
	Active super;
	TimeEvent te;
	uint8_t frame_rate;
	UART_HandleTypeDef * uart_handler;
} ScreenFrame;

void ScreenFrame_ctor(ScreenFrame * me);


#endif
