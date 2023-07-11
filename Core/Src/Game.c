#include "Game.h"

extern Active *AO_ScreenFrame;

static State Game_initial(Game *const me, UserInputEvent const *const e);
static State Game_welcome(Game *const me, UserInputEvent const *const e);
static State Game_updateLevel(Game *const me, UserInputEvent const *const e);
static State Game_playing(Game *const me, UserInputEvent const *const e);
static State Game_updateFrame(Game *const me, UserInputEvent const *const e);
static State Game_gameover(Game *const me, UserInputEvent const *const e);

void Game_ctor(Game *me) {
	Active_ctor(&me->super, (StateHandler) &Game_initial);
	TimeEvent_ctor(&me->update_time_te, APPLE_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->update_frame_te, APPLE_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->gen_apple_te, APPLE_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->gen_enemy_te, APPLE_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->gen_pwr_te, APPLE_TIMEOUT_SIG, &me->super);

}

static State Game_initial(Game *const me, UserInputEvent const *const e) {
	return TRAN(&Game_welcome);
}

static State Game_welcome(Game *const me, UserInputEvent const *const e) {
	State status;
	static const char welcome[] =
			"Welcome to Snake game\r\ns:to start game\r\ne:to end game\r\n5 to move the snake upwards,\r\n2 for downwards,\r\n1 for left,\r\n3 for right\r\n";
	switch (((Event*) e)->sig) {
	case ENTRY_SIG:
		//activate the ScreenFrame AO, send it an event with a pointer to the char * welcomeScreen
		status = HANDLED_STATUS;
		break;
	case USER_IN_SIG:
		if (e->user_in == 's') {
			//initialize the game attributes
			me->curr_lvl = 1;
			me->max_lvl = 5;
			me->curr_score = 0;
			me->highest_score = 0;
			me->elapsed_time = 0;
			me->game_speed = 1; // level 1 speed
			me->snake.head.row = 2;
			me->snake.head.col = 6;
			me->snake.tail.row = 2;
			me->snake.tail.col = 2;
			me->curr_dir = 0;
			me->d_pwr_factor = 1;
			me->s_pwr_factor = 1;
			me->num_normal_smbl = 0;
			me->num_pwr_smbl = 0;
			me->max_pwr_smbl = 20;
			me->max_total_smbl = 40;
			status = TRAN(&Game_updateLevel);
		} else {
			status = HANDLED_STATUS;
		}
		break;
	default:
		status = IGNORED_STATUS;
	}

	return status;
}
