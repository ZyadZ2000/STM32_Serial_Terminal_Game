#ifndef EVENTS_H
#define EVENTS_H

#include "freertos_ao.h"

typedef struct {
	Event super;
	char * frame;
	uint16_t frame_len;
} ScreenFrameEvent;

#endif
