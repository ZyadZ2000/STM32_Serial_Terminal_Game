#ifndef FREERTOS_AO_H
#define FREERTOS_AO_H

#include <stdint.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*------------------------Event Class------------------------------*/

typedef uint16_t Signal; /* event signal */

enum ReservedSignals {
	INIT_SIG, ENTRY_SIG, EXIT_SIG, USER_SIG /* first signal available to the users */
};

typedef struct {
	Signal sig; /* event signal */
} Event;

/*------------------------Finite State Machine Class------------------------------*/

typedef struct Fsm Fsm;

typedef enum {
	TRAN_STATUS, HANDLED_STATUS, IGNORED_STATUS, INIT_STATUS
} State;

typedef State (*StateHandler)(Fsm *const me, Event const *const e);

#define TRAN(target_) (((Fsm *)me)->state = (StateHandler)(target_), TRAN_STATUS)

struct Fsm {
	StateHandler state;
};

void Fsm_ctor(Fsm *const me, StateHandler initial);
void Fsm_init(Fsm *const me, Event const *const e);
void Fsm_dispatch(Fsm *const me, Event const *const e);

/*------------------------Active Object Class------------------------------*/

typedef struct Active Active;
struct Active {
	Fsm super; /* inherit Fsm */

	TaskHandle_t thread; /* private thread */
	QueueHandle_t queue; /* private message queue */
};

void Active_ctor(Active *const me, StateHandler initial);
void Active_start(Active *const me, uint8_t prio, Event **const queue_sto,
		uint32_t queue_len, StaticQueue_t *const queue_buffer,
		uint32_t *const stack_sto, uint32_t stack_size,
		StaticTask_t *const task_buffer);
void Active_post(Active *const me, Event const *const e);

/*------------------------Time Event Class------------------------------*/

typedef struct {
	Event super; /* inherit Event */
	Active *act; /* the AO that requested this TimeEvent */
	uint32_t timeout; /* timeout counter; 0 means not armed */
	uint32_t interval; /* interval for periodic TimeEvent, 0 means one-shot */
} TimeEvent;

void TimeEvent_ctor(TimeEvent *const me, Signal sig, Active *act);
void TimeEvent_arm(TimeEvent *const me, uint32_t timeout, uint32_t interval);
void TimeEvent_disarm(TimeEvent *const me);

/* static method: call this function in each RTOS tick */
void TimeEvent_tick(void);

#endif
