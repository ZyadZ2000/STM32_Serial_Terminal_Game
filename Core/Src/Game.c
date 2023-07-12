#include "Game.h"

extern Active *AO_ScreenFrame;

static char game_frame[FRAME_ROWS][FRAME_COLS]; //The entire game frame.
static const uint16_t game_speed_arr[MAX_NUM_LVLS] = { LVL1_SPEED, LVL2_SPEED,
LVL3_SPEED, LVL4_SPEED, LVL5_SPEED };
static const char pwr_smbl_arr[NUM_PWR_SMBL] = { 'S', 'D' };

static State Game_initial(Game *const me, UserInputEvent const *const e);
static State Game_welcome(Game *const me, UserInputEvent const *const e);
static State Game_startGame(Game *const me, UserInputEvent const *const e);
static State Game_startLevel(Game *const me, UserInputEvent const *const e);
static State Game_playing(Game *const me, UserInputEvent const *const e);
static State Game_win(Game *const me, UserInputEvent const *const e);
static State Game_lose(Game *const me, UserInputEvent const *const e);

static uint32_t random(void);
static void GameFrame_clearSymbols(void);
static void GameFrame_init(void);

void Game_ctor(Game *me) {
	Active_ctor(&me->super, (StateHandler) &Game_initial);
	TimeEvent_ctor(&me->update_time_te, ONE_SEC_SIG, &me->super);
	TimeEvent_ctor(&me->update_level_te, LVL_FINSIH_SIG, &me->super);
	TimeEvent_ctor(&me->update_dir_te, DIR_UPDATE_SIG, &me->super);
	TimeEvent_ctor(&me->gen_apple_te, GEN_APPLE_SIG, &me->super);
	TimeEvent_ctor(&me->gen_enemy_te, GEN_ENEMY_SIG, &me->super);
	TimeEvent_ctor(&me->gen_pwr_te, GEN_PWR_SIG, &me->super);
	TimeEvent_ctor(&me->clr_smbl_te, CLR_SMBL_SIG, &me->super);
	TimeEvent_ctor(&me->rm_d_pwr, D_PWR_TIMEOUT_SIG, &me->super);
	TimeEvent_ctor(&me->rm_s_pwr, S_PWR_TIMEOUT_SIG, &me->super);
}

static State Game_initial(Game *const me, UserInputEvent const *const e) {
	return TRAN(&Game_welcome);
}

static State Game_welcome(Game *const me, UserInputEvent const *const e) {
	State status;
	static const char welcome[] =
			"Welcome to Snake game\r\ns:to start game\r\nr:to reset game\r\n5 to move the snake upwards,\r\n2 for downwards,\r\n1 for left,\r\n3 for right\r\nYou lose if you eat an 'E' or eat yourself\r\n";
	switch (((Event*) e)->sig) {
	case ENTRY_SIG:
		//send ScreenFrame AO an event with a pointer to the welcome array
		ScreenFrameEvent e = { { SCREEN_FRAME_SIG }, welcome, sizeof(welcome) };
		Active_post(AO_ScreenFrame, (Event*) e);
		status = HANDLED_STATUS;
		break;
	case USER_IN_SIG:
		if (e->user_in == 's') {
			me->max_lvl = 5;
			me->highest_score = 0;
			status = TRAN(&Game_startGame);
		} else {
			status = HANDLED_STATUS;
		}
		break;
	default:
		status = IGNORED_STATUS;
	}

	return status;
}

static State Game_startGame(Game *const me, UserInputEvent const *const e) {
	State status;
	switch (((Event*) e)->sig) {
	case ENTRY_SIG:
		//initialize the game frame
		GameFrame_init();
		//initialize the game attributes
		me->curr_lvl = 1;
		me->curr_score = 0;
		me->elapsed_time = 0;
		me->snake.head.row = 2;
		me->snake.head.col = 6;
		me->snake.tail.row = 2;
		me->snake.tail.col = 2;
		me->curr_dir = 0;
		me->d_pwr_factor = 1;
		me->is_s_pwr = false;
		ScreenFrameEvent e = { { SCREEN_FRAME_SIG }, game_frame,
				sizeof(game_frame) };
		Active_post(AO_ScreenFrame, (Event*) e);
		status = HANDLED_STATUS;
		break;
	case USER_IN_SIG:
		if (e->user_in == '1' || e->user_in == '2' || e->user_in == '3'
				|| e->user_in == '5') {
			me->curr_dir = e->user_in;
			TimeEvent_arm(&me->update_time_te, configTICK_RATE_HZ,
					configTICK_RATE_HZ);
			status = TRAN(&Game_startLevel);
		} else {
			status = HANDLED_STATUS;
		}
		break;
	default:
		status = IGNORED_STATUS;
	}

	return status;
}

static State Game_startLevel(Game *const me, UserInputEvent const *const e) {
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

//Random generation using the XOR shift.
static uint32_t random(void) {
	static u32 x = 10, y = 630, z = 100, w = 263;
	u32 t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

static void GameFrame_clearSymbols(void) {
	uint8_t i, j;
	for (i = 0; i < FRAME_ROWS; i++) {
		for (j = 0; j < FRAME_COLS; j++) {
			if (frame[i][j]
					== 'D'|| frame[i][j] == 'S' || frame[i][j] == APPLE_SMBL || frame[i][j] == ENEMY_SMBL) {
				frame[i][j] = ' ';
			}
		}
	}
}

static void GameFrame_init(void) {
	uint8_t i, j;
	for (i = 0; i < FRAME_ROWS; i++) {
		for (j = 0; j < FRAME_COLS; j++) {
			if (i == 0 || i == (FRAME_ROWS - 1)) {
				if (j == (FRAME_COLS - 2)) {
					game_game_frame[i][j] = '\r';
				} else if (j == (FRAME_COLS - 1)) {
					if (i == (FRAME_ROWS - 1)) {
						game_game_frame[i][j] = '\0';
					} else {
						game_game_frame[i][j] = '\n';
					}
				} else {
					game_game_frame[i][j] = '#';
				}
			} else {
				if (j == (FRAME_COLS - 2)) {
					game_game_frame[i][j] = '\r';
				} else if (j == (FRAME_COLS - 1)) {
					game_game_frame[i][j] = '\n';
				} else {
					if (j == 0 || j == (FRAME_COLS - 3)) {
						game_game_frame[i][j] = '#';
						game_game_frame[i][j] = '#';
					} else {
						game_game_frame[i][j] = ' ';
					}
				}
			}
		}
	}
	for (i = 0; i < 5 - 1; i++) {
		game_frame[2][i + 2] = '*';
	}
	game_frame[2][5 + 1] = '&';
}

