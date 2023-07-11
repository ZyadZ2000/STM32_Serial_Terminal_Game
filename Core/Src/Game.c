#include "Game.h"

extern Active *AO_ScreenFrame;

static const char game_frame = ""; //The entire game frame.
static const uint16_t game_speed_arr[] = { LVL1_SPD, LVL2_SPD, LVL3_SPD,
LVL4_SPD, LVL5_SPD, LVL6_SPD };

static State Game_initial(Game *const me, UserInputEvent const *const e);
static State Game_welcome(Game *const me, UserInputEvent const *const e);
static State Game_updateLevel(Game *const me, UserInputEvent const *const e);
static State Game_playing(Game *const me, UserInputEvent const *const e);
static State Game_updateFrame(Game *const me, UserInputEvent const *const e);
static State Game_gameover(Game *const me, UserInputEvent const *const e);
static uint32_t random(void);

//Random generation using the XOR shift.
uint32_t random(void) {
	static u32 x = 10, y = 630, z = 100, w = 263;
	u32 t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

void Game_ctor(Game *me) {
	Active_ctor(&me->super, (StateHandler) &Game_initial);
	TimeEvent_ctor(&me->update_time_te, ELAPSED_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->update_frame_te, UPDATE_FRAME_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->update_level_te, UPDATE_LVL_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->gen_apple_te, APPLE_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->gen_enemy_te, ENEMY_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->gen_pwr_te, PWR_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->clr_pwr_te, CLR_PWR_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->rm_d_pwr, REMOVE_DOUBLE_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->rm_s_pwr, REMOVE_SLOW_TIMEOUT_SIG, &me->super);
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
		//send ScreenFrame AO an event with a pointer to the char * welcomeScreen
		ScreenFrameEvent e = { { SCREEN_FRAME_SIG }, welcome, sizeof(welcome) };
		Active_post(AO_ScreenFrame, (Event*) e);
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
			me->snake.head.row = 2;
			me->snake.head.col = 6;
			me->snake.tail.row = 2;
			me->snake.tail.col = 2;
			me->curr_dir = 0;
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

static State Game_updateLevel(Game *const me, UserInputEvent const *const e) {
	State status;
	switch (((Event*) e)->sig) {
	case ENTRY_SIG:
		TimeEvent_disarm(&me->update_frame_te);
		TimeEvent_disarm(&me->update_level_te);

		TimeEvent_disarm(&me->gen_apple_te);
		TimeEvent_disarm(&me->gen_enemy_te);
		TimeEvent_disarm(&me->gen_pwr_te);
		TimeEvent_disarm(&me->clr_pwr_te);
		TimeEvent_disarm(&me->rm_d_pwr);
		TimeEvent_disarm(&me->rm_s_pwr);

		if (me->curr_lvl == me->max_lvl + 1) {
			TimeEvent_disarm(&me->update_time_te);
			status = TRAN(&Game_gameover);
		} else {
			if (me->curr_lvl == 1) {
				TimeEvent_arm(&me->update_time_te, configTICK_RATE_HZ / 1U,
				configTICK_RATE_HZ / 1U);
			}
			me->game_speed = game_speed_arr[me->curr_lvl - 1]; // level 1 speed
			me->d_pwr_factor = 1;
			me->s_pwr_factor = 1;
			me->num_normal_smbl = 0;
			me->num_pwr_smbl = 0;
			TimeEvent_arm(&me->update_frame_te, me->game_speed, me->game_speed);
			TimeEvent_arm(&me->gen_apple_te, (me->game_speed) * 2,
			configTICK_RATE_HZ / 1U);
			TimeEvent_arm(&me->gen_enemy_te, configTICK_RATE_HZ / 1U,
			configTICK_RATE_HZ / 1U);
			TimeEvent_arm(&me->gen_pwr_te, configTICK_RATE_HZ / 1U,
			configTICK_RATE_HZ / 1U);
			TimeEvent_arm(&me->clr_pwr_te, configTICK_RATE_HZ / 1U,
			configTICK_RATE_HZ / 1U);

			//clear the frame of all the symbols
			status = TRAN(&Game_playing);
		}
		break;
	default:
		status = IGNORED_STATUS;
		break;
	}
}
