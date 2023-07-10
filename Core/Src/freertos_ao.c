#include "freertos_ao.h"

/*---------------------------------------------------------------------------*/

static Event const entryEvt = { ENTRY_SIG };
static Event const exitEvt = { EXIT_SIG };

void Fsm_ctor(Fsm *const me, StateHandler initial) {
	me->state = initial;
}

void Fsm_init(Fsm *const me, Event const *const e) {
	(*me->state)(me, e);
	(*me->state)(me, &entryEvt);
}

void Fsm_dispatch(Fsm *const me, Event const *const e) {
	State status;
	StateHandler prev_state = me->state; /* save for later */

	status = (*me->state)(me, e);

	if (status == TRAN_STATUS) { /* transition taken? */
		(*prev_state)(me, &exitEvt);
		(*me->state)(me, &entryEvt);
	}
}

/*..........................................................................*/
void Active_ctor(Active *const me, StateHandler initial) {
	Fsm_ctor(&me->super, initial);
}

/*..........................................................................*/
/* Thread function for all Active Objects (uC/OS-II task signature) */
static void Active_eventLoop(void *pdata) {
	Active *me = (Active*) pdata; /* the AO instance "me" */

	/* initialize the AO */
	Fsm_init(&me->super, (Event*) 0);

	/* event loop ("message pump") */
	while (1) {
		Event *e; /* pointer to event object ("message") */
		BaseType_t receiveStatus; /* uC/OS-II error status */

		/* wait for any event and receive it into object 'e' */
		receiveStatus = xQueueReceive(me->queue, &e, portMAX_DELAY); /* BLOCKING! */

		if (receiveStatus == pdTRUE) {
			/* dispatch event to the active object 'me' */
			Fsm_dispatch(&me->super, e); /* NO BLOCKING! */
		}
	}
}

/*..........................................................................*/
void Active_start(Active *const me, uint8_t priority, Event **const queueSto,
		uint32_t queueLen, StaticQueue_t *queueBuffer, uint32_t *const stackSto,
		uint32_t stackSize, StaticTask_t *const taskTCBBuffer) {

	me->queue = xQueueCreateStatic(queueLen, sizeof(Event*),
			(uint8_t*) queueSto, queueBuffer);
	me->thread = priority;
	xTaskCreateStatic(&Active_eventLoop, NULL, stackSize, me, priority, stackSto,
			taskTCBBuffer);
}

/*..........................................................................*/
void Active_post(Active *const me, Event const *const e) {
	xQueueSendToBack(me->queue, (void*) &e, portMAX_DELAY);
}

/*--------------------------------------------------------------------------*/
/* Time Event services... */

static TimeEvent *l_tevt[10]; /* all TimeEvents in the application */
static uint_fast8_t l_tevtNum; /* current number of TimeEvents */

/*..........................................................................*/
void TimeEvent_ctor(TimeEvent *const me, Signal sig, Active *act) {
	/* no critical section because it is presumed that all TimeEvents
	 * are created *before* multitasking has started.
	 */
	me->super.sig = sig;
	me->act = act;
	me->timeout = 0U;
	me->interval = 0U;

	/* register one more TimeEvent instance */
	taskENTER_CRITICAL();
	l_tevt[l_tevtNum] = me;
	++l_tevtNum;
	taskEXIT_CRITICAL();
}

/*..........................................................................*/
void TimeEvent_arm(TimeEvent *const me, uint32_t timeout, uint32_t interval) {
	taskENTER_CRITICAL();
	me->timeout = timeout;
	me->interval = interval;
	taskEXIT_CRITICAL();
}

/*..........................................................................*/
void TimeEvent_disarm(TimeEvent *const me) {
	taskENTER_CRITICAL();
	me->timeout = 0U;
	taskEXIT_CRITICAL();
}

/*..........................................................................*/
void TimeEvent_tick(void) {
	uint_fast8_t i;
	for (i = 0U; i < l_tevtNum; ++i) {
		TimeEvent *const t = l_tevt[i];
		if (t->timeout > 0U) { /* is this TimeEvent armed? */
			if (--t->timeout == 0U) { /* is it expiring now? */
				Active_post(t->act, &t->super);
				t->timeout = t->interval; /* rearm or disarm (one-shot) */
			}
		}
	}
}

