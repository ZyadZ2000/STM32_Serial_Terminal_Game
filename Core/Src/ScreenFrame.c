#include "ScreenFrame.h"

static State ScreenFrame_initial(ScreenFrame *const me,
		ScreenFrameEvent const *const e);
static State ScreenFrame_wait4game(ScreenFrame *const me,
		ScreenFrameEvent const *const e);
static State ScreenFrame_sendFrame(ScreenFrame *const me,
		ScreenFrameEvent const *const e);

void ScreenFrame_ctor(ScreenFrame *me, UART_HandleTypeDef *uart) {
	Active_ctor(&me->super, (StateHandler) &ScreenFrame_initial);
	TimeEvent_ctor(&me->te, TIMEOUT_SIG, &me->super);
	me->uart = uart;
}

static State ScreenFrame_initial(ScreenFrame *const me,
		ScreenFrameEvent const *const e) {
	return TRAN(&ScreenFrame_wait4game);
}

static State ScreenFrame_wait4game(ScreenFrame *const me,
		ScreenFrameEvent const *const e) {
	State status;
	switch (((Event*) e)->sig) {
	case SCREEN_FRAME_SIG: {
		me->frame = e->frame;
		me->frame_len = e->frame_len;
		me->frame_rate = 30;
		TimeEvent_arm(&me->te, configTICK_RATE_HZ / me->frame_rate,
				configTICK_RATE_HZ / me->frame_rate);
		status = TRAN(&ScreenFrame_sendFrame);
		break;
	}
	default: {
		status = IGNORED_STATUS;
	}
	}

	return status;
}

static State ScreenFrame_sendFrame(ScreenFrame *const me,
		ScreenFrameEvent const *const e) {
	State status;
	char * clearScreen = "\x1b[2J\x1b[H";
	switch (((Event*) e)->sig) {
	case ENTRY_SIG:
	case TIMEOUT_SIG: {
		HAL_UART_Transmit(me->uart, (uint8_t *) clearScreen , sizeof(clearScreen),
				10000);
		HAL_UART_Transmit(me->uart, (uint8_t *) e->frame, e->frame_len, 10000);
		status = HANDLED_STATUS;
	}
	case SCREEN_FRAME_SIG: {
		me->frame = e->frame;
		me->frame_len = e->frame_len;
		status = HANDLED_STATUS;
		break;
	}
	default: {
		status = IGNORED_STATUS;
	}
	}

	return status;
}
