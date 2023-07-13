#ifndef SCREENFRAME_H
#define SCREENFRAME_H

#include "stm32f4xx_hal.h"
#include "freertos_ao.h"
#include "signals.h"
#include "events.h"

typedef struct {
	Active super;
	char * frame;
	uint16_t frame_len;
	uint8_t frame_rate;
	TimeEvent te;
	UART_HandleTypeDef * uart;
}ScreenFrame;

void ScreenFrame_ctor(ScreenFrame * me, UART_HandleTypeDef * uart);

#endif
