#include "ScreenFrame.h"

static State ScreenFrame_initial(ScreenFrame *const me, ScreenFrameEvent const *const e);
static State ScreenFrame_update(ScreenFrame *const me, ScreenFrameEvent const *const e);

void ScreenFrame_ctor(ScreenFrame *me, UART_HandleTypeDef * uart_handler) {
	Active_ctor(&me->super, (StateHandler) &ScreenFrame_initial);
	TimeEvent_ctor(&me->te, TIMEOUT_SIG, &me->super);
	me->uart_handler = uart_handler;
}

static State ScreenFrame_initial(ScreenFrame *const me, ScreenFrameEvent const *const e) {
	me->frame_rate = 10;
    TimeEvent_arm(&me->te, configTICK_RATE_HZ / me->frame_rate, configTICK_RATE_HZ / me->frame_rate);
    return TRAN(&ScreenFrame_update);
}

static State ScreenFrame_update(ScreenFrame *const me, ScreenFrameEvent const *const e) {
	State status;
	switch (e->sig) {
		case TIMEOUT_SIG: {
			//make some assertions, calculate the timeout.
			HAL_UART_Transmit(me->uart_handler, e->frame, e->frame_len, 1200 / me->frame_rate);
			status = HANDLED_STATUS;
			break;
		}
		default: {
			status = IGNORED_STATUS;
		}
	}

	return status;
}
