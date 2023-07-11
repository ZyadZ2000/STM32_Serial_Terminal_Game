#ifndef FREERTOS_AO_H
#define FREERTOS_AO_H

#include <stdint.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*---------------------------------------------------------------------------*/
/* Event Class */

typedef uint16_t Signal; /* event signal */

enum ReservedSignals {
	INIT_SIG, /* dispatched to AO before entering event-loop */
	ENTRY_SIG, /* for triggering the entry action in a state */
	EXIT_SIG, /* for triggering the exit action from a state */
	USER_SIG /* first signal available to the users */
};

typedef struct {
	Signal sig; /* event signal */
/* event parameters added in subclasses of Event */
} Event;

/*---------------------------------------------------------------------------*/
/* Finite State Machine Class*/
typedef struct Fsm Fsm; /* forward declaration */

typedef enum {
	TRAN_STATUS, HANDLED_STATUS, IGNORED_STATUS, INIT_STATUS
} State;

typedef State (*StateHandler)(Fsm *const me, Event const *const e);

#define TRAN(target_) (((Fsm *)me)->state = (StateHandler)(target_), TRAN_STATUS)

struct Fsm {
	StateHandler state; /* the "state variable" */
};

void Fsm_ctor(Fsm *const me, StateHandler initial);
void Fsm_init(Fsm *const me, Event const *const e);
void Fsm_dispatch(Fsm *const me, Event const *const e);

/*---------------------------------------------------------------------------*/
/* Active Object Class */

typedef struct Active Active; /* forward declaration */

struct Active {
	Fsm super; /* inherit Fsm */

	TaskHandle_t thread; /* private thread (the unique uC/OS-II task priority) */
	QueueHandle_t queue; /* private message queue */

/* active object data added in subclasses of Active */
};

void Active_ctor(Active *const me, StateHandler initial);
void Active_start(Active *const me, uint8_t priority, Event **const queueSto,
		uint32_t queueLen, StaticQueue_t *const queueBuffer,
		uint32_t *const stackSto, uint32_t stackSize,
		StaticTask_t *const taskTCBBuffer);
void Active_post(Active *const me, Event const *const e);

/*---------------------------------------------------------------------------*/
/* Time Event Class */

typedef struct {
	Event super; /* inherit Event */
	Active *act; /* the AO that requested this TimeEvent */
	uint32_t timeout; /* timeout counter; 0 means not armed */
	uint32_t interval; /* interval for periodic TimeEvent, 0 means one-shot */
} TimeEvent;

void TimeEvent_ctor(TimeEvent *const me, Signal sig, Active *act);
void TimeEvent_arm(TimeEvent *const me, uint32_t timeout, uint32_t interval);
void TimeEvent_disarm(TimeEvent *const me);

/* static (i.e., class-wide) operation */
void TimeEvent_tick(void);

#endif
