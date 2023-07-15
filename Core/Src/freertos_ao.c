#include "freertos_ao.h"

static Event const entryEvt = { ENTRY_SIG };
static Event const exitEvt = { EXIT_SIG };

void Fsm_ctor(Fsm *const me, StateHandler initial) {
	me->state = initial;
}

void Fsm_init(Fsm *const me, Event const *const e) {
	configASSERT(me->state != (StateHandler )0);
	(*me->state)(me, e);
	(*me->state)(me, &entryEvt);
}

void Fsm_dispatch(Fsm *const me, Event const *const e) {
	State status;
	StateHandler prev_state = me->state; /* save for later */

	configASSERT(me->state != (StateHandler ) 0);
	status = (*me->state)(me, e);

	if (status == TRAN_STATUS) { /* transition taken? */
		(*prev_state)(me, &exitEvt);
		(*me->state)(me, &entryEvt);
	}
}

void Active_ctor(Active *const me, StateHandler initial) {
	Fsm_ctor(&me->super, initial);
}

static void Active_eventLoop(void *pdata) {
	Active *me = (Active*) pdata; /* the AO instance "me" */

	/* initialize the AO */
	Fsm_init(&me->super, (Event*) 0);

	/* event loop ("message pump") */
	while (1) {
		Event *e; /* pointer to event object ("message") */
		BaseType_t receiveStatus;

		/* wait for any event and receive it into object 'e' */
		receiveStatus = xQueueReceive(me->queue, &e, portMAX_DELAY); /* BLOCKING! */
		configASSERT(receiveStatus == pdTRUE);

		/* dispatch event to the active object 'me' */
		Fsm_dispatch(&me->super, e);

	}
}

void Active_start(Active *const me, uint8_t prio, Event **const queue_sto,
		uint32_t queue_len, uint32_t *const stack_sto, uint32_t stack_size) {

	configASSERT(me && (0 < prio) && (prio < configMAX_PRIORITIES));
	me->queue = xQueueCreateStatic(queue_len, sizeof(Event*),
			(uint8_t* ) queue_sto, &me->queue_cb);
	configASSERT(me->queue);

	me->thread = xTaskCreateStatic(&Active_eventLoop, NULL, stack_size,
			(void*) me, prio, stack_sto, &me->thread_cb);
	configASSERT(me->thread);
}

void Active_post(Active *const me, Event const *const e) {
	BaseType_t state = xQueueSendToBack(me->queue, (void* ) &e, (TickType_t)0U);
	configASSERT(state == pdTRUE);
}

void Active_postFromISR(Active *const me, Event const *const e,
		BaseType_t *xHigherPriorityTaskWoken) {
	xQueueSendToBackFromISR(me->queue, (void* ) &e, xHigherPriorityTaskWoken);
}

/* Time Event services... */

static TimeEvent *l_tevt[10]; /* all TimeEvents in the application */
static uint_fast8_t l_tevtNum; /* current number of TimeEvents */

void TimeEvent_ctor(TimeEvent *const me, Signal sig, Active *act) {
	me->super.sig = sig;
	me->act = act;
	me->timeout = 0U;
	me->interval = 0U;

	/* register one more TimeEvent instance */
	taskENTER_CRITICAL();
	configASSERT(l_tevtNum < sizeof(l_tevt) / sizeof(l_tevt[0]));
	l_tevt[l_tevtNum] = me;
	++l_tevtNum;
	taskEXIT_CRITICAL();
}

void TimeEvent_arm(TimeEvent *const me, uint32_t timeout, uint32_t interval) {
	taskENTER_CRITICAL();
	me->timeout = timeout;
	me->interval = interval;
	taskEXIT_CRITICAL();
}

void TimeEvent_disarm(TimeEvent *const me) {
	taskENTER_CRITICAL();
	me->timeout = 0U;
	taskEXIT_CRITICAL();
}

void TimeEvent_tickFromISR(BaseType_t *xHigherPriorityTaskWoken) {
	uint_fast8_t i;
	for (i = 0U; i < l_tevtNum; ++i) {
		TimeEvent *const t = l_tevt[i];
		if (t->timeout > 0U) { /* is this TimeEvent armed? */
			if (--t->timeout == 0U) { /* is it expiring now? */
				Active_postFromISR(t->act, &t->super,xHigherPriorityTaskWoken);
				t->timeout = t->interval; /* rearm or disarm (one-shot) */
			}
		}
	}
}

/* Enable the Tick Hook in FreeRTOSConfig to use time events*/
void vApplicationTickHook(void) {
	BaseType_t xHigherPriorityTaskWoken;
	TimeEvent_tickFromISR(&xHigherPriorityTaskWoken);
}

