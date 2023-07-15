#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Game.h"

extern Active *AO_ScreenFrame;

static char game_frame[FRAME_ROWS + 2][FRAME_COLS]; //The entire game frame.
static const uint16_t game_speed_arr[MAX_NUM_LVLS] = { LVL1_SPEED, LVL2_SPEED,
LVL3_SPEED, LVL4_SPEED, LVL5_SPEED };
static const char pwr_smbl_arr[NUM_PWR_SMBL] = { 'S', 'D' };
static ScreenFrameEvent se = { { SCREEN_FRAME_SIG } };
static int8_t user_input;

static State Game_initial(Game *const me, Event const *const e);
static State Game_welcome(Game *const me, Event const *const e);
static State Game_startGame(Game *const me, Event const *const e);
static State Game_startLevel(Game *const me, Event const *const e);
static State Game_playing(Game *const me, Event const *const e);
static State Game_win(Game *const me, Event const *const e);
static State Game_lose(Game *const me, Event const *const e);
static State Game_moveSnake(Game *const me, uint8_t row_dir, uint8_t col_dir);
static uint32_t Game_randomGenerator(void);
static void GameFrame_clearSymbols(void);
static void GameFrame_init(Snake *snake);

void Game_ctor(Game *me, UART_HandleTypeDef *uart) {
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
	me->uart = uart;
}

static State Game_initial(Game *const me, Event const *const e) {
	return TRAN(&Game_welcome);
}

static State Game_welcome(Game *const me, Event const *const e) {
	State status;
	static const char welcome[] =
			"Welcome to Snake game\r\ns:to start game\r\nr:to reset game\r\n5 to move the snake up,\r\n2 for down,\r\n1 for left,\r\n3 for right\r\nYou lose if you hit the wall, eat an 'E', or eat yourself\r\n";
	switch (e->sig) {
	case ENTRY_SIG: {
		//send ScreenFrame AO an event with a pointer to the welcome array
		se.frame = (char*) welcome;
		se.frame_len = sizeof(welcome);
		Active_post(AO_ScreenFrame, (Event*) &se);
		HAL_UART_Receive_IT(me->uart, (uint8_t*) &user_input, 1U);
		status = HANDLED_STATUS;
		break;
	}
	case USER_IN_SIG: {
		if (user_input == 's') {
			me->max_lvl = MAX_NUM_LVLS;
			me->highest_score = 0;
			status = TRAN(&Game_startGame);
		} else {
			status = HANDLED_STATUS;
		}
		HAL_UART_Receive_IT(me->uart, (uint8_t*) &user_input, 1U);
		break;
	}
	default: {
		status = IGNORED_STATUS;
	}
	}

	return status;
}

static State Game_startGame(Game *const me, Event const *const e) {
	State status;
	switch (e->sig) {
	case ENTRY_SIG:
		//initialize the game frame and snake position
		GameFrame_init(&me->snake);
		//initialize the game attributes
		me->curr_lvl = 1;
		me->curr_score = 0;
		me->elapsed_time = 0;
		me->curr_dir = 0;
		me->d_pwr_factor = 1;
		me->is_s_pwr = false;
		se.frame = (char*) game_frame;
		se.frame_len = sizeof(game_frame);
		Active_post(AO_ScreenFrame, (Event*) &se);
		status = HANDLED_STATUS;
		break;
	case USER_IN_SIG:
		if (user_input == '1' || user_input == '2' || user_input == '3'
				|| user_input == '5') {
			me->curr_dir = user_input;
			TimeEvent_arm(&me->update_time_te, configTICK_RATE_HZ,
			configTICK_RATE_HZ);
			status = TRAN(&Game_startLevel);
		} else {
			status = HANDLED_STATUS;
		}
		HAL_UART_Receive_IT(me->uart, (uint8_t*) &user_input, 1U);
		break;
	default:
		status = IGNORED_STATUS;
	}

	return status;
}

static State Game_startLevel(Game *const me, Event const *const e) {
	State status;
	switch (e->sig) {
	case ENTRY_SIG:
		if (me->curr_lvl > 1) {
			taskENTER_CRITICAL();
			GameFrame_clearSymbols();
			taskEXIT_CRITICAL();
		}
		me->game_speed = game_speed_arr[me->curr_lvl - 1];
		TimeEvent_arm(&me->update_level_te, configTICK_RATE_HZ * 30U, 0);
		TimeEvent_arm(&me->clr_smbl_te, configTICK_RATE_HZ * 10U,
		configTICK_RATE_HZ * 10U);
		TimeEvent_arm(&me->update_dir_te, me->game_speed, me->game_speed);
		TimeEvent_arm(&me->gen_apple_te, (uint32_t) (me->game_speed * 1.50),
				(uint32_t) (me->game_speed * 1.50));
		TimeEvent_arm(&me->gen_enemy_te, (uint32_t) (me->game_speed * 3),
				(uint32_t) (me->game_speed * 3));
		TimeEvent_arm(&me->gen_pwr_te, configTICK_RATE_HZ * 2,
		configTICK_RATE_HZ * 2);

		//clear the frame of all the symbols
		status = TRAN(&Game_playing);
		break;
	default:
		status = IGNORED_STATUS;
		break;
	}
	return status;
}

static State Game_playing(Game *const me, Event const *const e) {
	State status;
	switch (e->sig) {
	case USER_IN_SIG:
		if (user_input == 'r') {
			status = TRAN(&Game_startGame);
		} else if (user_input == '1' || user_input == '2' || user_input == '3'
				|| user_input == '5') {
			me->curr_dir = user_input;
		}
		status = HANDLED_STATUS;
		HAL_UART_Receive_IT(me->uart, (uint8_t*) &user_input, 1U);
		break;
	case DIR_UPDATE_SIG:
		switch (me->curr_dir) {
		case '1':
			status = Game_moveSnake(me, 0, -1);
			break;
		case '2':
			status = Game_moveSnake(me, 1, 0);
			break;
		case '3':
			status = Game_moveSnake(me, 0, 1);
			break;
		case '5':
			status = Game_moveSnake(me, -1, 0);
			break;
		}
		break;
	case GEN_APPLE_SIG: {
		uint8_t row;
		uint8_t col;
		do {
			row = (uint8_t) (Game_randomGenerator() % FRAME_ROWS);
			col = (uint8_t) (Game_randomGenerator() % FRAME_COLS);
		} while (game_frame[row][col] != ' ');
		taskENTER_CRITICAL();
		game_frame[row][col] = APPLE_SMBL;
		taskEXIT_CRITICAL();
		status = HANDLED_STATUS;
		break;
	}
	case GEN_ENEMY_SIG: {
		uint8_t row;
		uint8_t col;
		do {
			row = (uint8_t) (Game_randomGenerator() % FRAME_ROWS);
			col = (uint8_t) (Game_randomGenerator() % FRAME_COLS);
		} while (game_frame[row][col] != ' ');
		taskENTER_CRITICAL();
		game_frame[row][col] = ENEMY_SMBL;
		taskEXIT_CRITICAL();
		status = HANDLED_STATUS;
		break;
	}
	case GEN_PWR_SIG: {
		uint8_t pwr = pwr_smbl_arr[Game_randomGenerator() % NUM_PWR_SMBL];
		uint8_t row;
		uint8_t col;
		do {
			row = (uint8_t) (Game_randomGenerator() % FRAME_ROWS);
			col = (uint8_t) (Game_randomGenerator() % FRAME_COLS);
		} while (game_frame[row][col] != ' ');
		taskENTER_CRITICAL();
		game_frame[row][col] = pwr;
		taskEXIT_CRITICAL();
		status = HANDLED_STATUS;
		break;
	}
	case CLR_SMBL_SIG: {
		taskENTER_CRITICAL();
		GameFrame_clearSymbols();
		taskEXIT_CRITICAL();
		status = HANDLED_STATUS;
		break;
	}
	case D_PWR_TIMEOUT_SIG: {
		me->d_pwr_factor = 1;
		status = HANDLED_STATUS;
		break;
	}
	case S_PWR_TIMEOUT_SIG: {
		TimeEvent_disarm(&me->gen_enemy_te);
		TimeEvent_arm(&me->gen_enemy_te, (uint32_t) (me->game_speed * 3),
				(uint32_t) (me->game_speed * 3));
		status = HANDLED_STATUS;
		break;
	}
	case LVL_FINSIH_SIG: {
		if (me->curr_lvl == me->max_lvl)
			status = TRAN(&Game_win);
		else {
			me->curr_lvl++;
			status = TRAN(&Game_startLevel);
		}
		break;
	}
	case ONE_SEC_SIG: {
		me->elapsed_time++;
		char buffer[6];
		itoa(me->elapsed_time, buffer, 10);
		taskENTER_CRITICAL();
		strcpy(&game_frame[FRAME_ROWS + 1][6], buffer);
		taskEXIT_CRITICAL();
		status = HANDLED_STATUS;
		break;
	}
	case EXIT_SIG: {
		TimeEvent_disarm(&me->update_level_te);
		TimeEvent_disarm(&me->update_dir_te);
		TimeEvent_disarm(&me->gen_apple_te);
		TimeEvent_disarm(&me->gen_enemy_te);
		TimeEvent_disarm(&me->gen_pwr_te);
		TimeEvent_disarm(&me->clr_smbl_te);
		TimeEvent_disarm(&me->rm_d_pwr);
		TimeEvent_disarm(&me->rm_s_pwr);
		status = HANDLED_STATUS;
		break;
	}
	default: {
		status = IGNORED_STATUS;
		break;
	}
	}
	return status;
}

static State Game_win(Game *const me, Event const *const e) {
	State status;
	static char win_frame[80];
	switch (e->sig) {
	case ENTRY_SIG: {
		TimeEvent_disarm(&me->update_time_te);
		if (me->curr_score >= me->highest_score)
			me->highest_score = me->curr_score;
		sprintf(win_frame,
				"YOU WIN!!!\r\nSCORE: %lu\r\nHEIGHEST SCORE: %lu\r\npress 'r' to restart\r\n",
				me->curr_score, me->highest_score);
		se.frame = win_frame;
		se.frame_len = strlen(win_frame);
		Active_post(AO_ScreenFrame, (Event*) &se);
		status = HANDLED_STATUS;
		break;
	}
	case USER_IN_SIG: {
		if (user_input == 'r') {
			status = TRAN(&Game_startGame);
		} else {
			status = HANDLED_STATUS;
		}
		HAL_UART_Receive_IT(me->uart, (uint8_t*) &user_input, 1U);
	}
	}
	return status;
}
static State Game_lose(Game *const me, Event const *const e) {
	State status;
	static char lose_frame[81];
	switch (e->sig) {
	case ENTRY_SIG: {
		TimeEvent_disarm(&me->update_time_te);
		if (me->curr_score >= me->highest_score)
			me->highest_score = me->curr_score;
		sprintf(lose_frame,
				"GAMEOVER!!!\r\nSCORE: %lu\r\nHEIGHEST SCORE: %lu\r\npress 'r' to restart\r\n",
				me->curr_score, me->highest_score);
		se.frame = lose_frame;
		se.frame_len = strlen(lose_frame);
		Active_post(AO_ScreenFrame, (Event*) &se);
		status = HANDLED_STATUS;
		break;
	}
	case USER_IN_SIG: {
		if (user_input == 'r') {
			status = TRAN(&Game_startGame);
		} else {
			status = HANDLED_STATUS;
		}
		HAL_UART_Receive_IT(me->uart, (uint8_t*) &user_input, 1U);
	}
	}
	return status;
}

//Random generation using the XOR shift.
static uint32_t Game_randomGenerator(void) {
	static uint32_t x = 10, y = 630, z = 100, w = 263;
	uint32_t t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

static void GameFrame_clearSymbols(void) {
	uint8_t i, j;
	for (i = 0; i < FRAME_ROWS; i++) {
		for (j = 0; j < FRAME_COLS; j++) {
			if (game_frame[i][j]
					== 'D'|| game_frame[i][j] == 'S' || game_frame[i][j] == APPLE_SMBL || game_frame[i][j] == ENEMY_SMBL) {
				game_frame[i][j] = ' ';
			}
		}
	}
}

static void GameFrame_init(Snake *snake) {
	uint8_t i, j;
	for (i = 0; i < FRAME_ROWS; i++) {
		for (j = 0; j < FRAME_COLS; j++) {
			if (i == 0 || i == (FRAME_ROWS - 1)) {
				if (j == (FRAME_COLS - 2)) {
					game_frame[i][j] = '\r';
				} else if (j == (FRAME_COLS - 1)) {
					if (i == (FRAME_ROWS - 1)) {
						game_frame[i][j] = '\0';
					} else {
						game_frame[i][j] = '\n';
					}
				} else {
					game_frame[i][j] = '#';
				}
			} else {
				if (j == (FRAME_COLS - 2)) {
					game_frame[i][j] = '\r';
				} else if (j == (FRAME_COLS - 1)) {
					game_frame[i][j] = '\n';
				} else {
					if (j == 0 || j == (FRAME_COLS - 3)) {
						game_frame[i][j] = '#';
						game_frame[i][j] = '#';
					} else {
						game_frame[i][j] = ' ';
					}
				}
			}
		}
	}
	strcpy(game_frame[FRAME_ROWS], "Score: 0");
	for (i = 8; i < FRAME_COLS; i++) {
		if (i == (FRAME_COLS - 2)) {
			game_frame[FRAME_ROWS][i] = '\r';
		} else if (i == (FRAME_COLS - 1)) {
			game_frame[FRAME_ROWS][i] = '\n';
		} else {
			game_frame[FRAME_ROWS][i] = ' ';
		}
	}
	strcpy(game_frame[FRAME_ROWS + 1], "Time: 0");
	for (i = 7; i < FRAME_COLS; i++) {
		if (i == (FRAME_COLS - 2)) {
			game_frame[FRAME_ROWS + 1][i] = '\r';
		} else if (i == (FRAME_COLS - 1)) {
			game_frame[FRAME_ROWS + 1][i] = '\n';
		} else {
			game_frame[FRAME_ROWS + 1][i] = ' ';
		}
	}

	for (i = 2; i < 6; i++) {
		game_frame[2][i] = '*';
	}
	game_frame[2][6] = '&';
	snake->head.row = 2;
	snake->head.col = 6;
	snake->tail.row = 2;
	snake->tail.col = 2;
}

static State Game_moveSnake(Game *const me, uint8_t row_dir, uint8_t col_dir) {
	switch (game_frame[me->snake.head.row + row_dir][me->snake.head.col
			+ col_dir]) {
	case '#':
	case 'E':
	case '*':
		return TRAN(&Game_lose);
	case 'A':
		me->curr_score += 1 * me->d_pwr_factor;
		char buffer[6];
		itoa(me->curr_score, buffer, 10);
		taskENTER_CRITICAL();
		game_frame[me->snake.head.row][me->snake.head.col] = '*';
		game_frame[me->snake.head.row + row_dir][me->snake.head.col + col_dir] =
				'&';
		strcpy(&game_frame[FRAME_ROWS][7], buffer);
		taskEXIT_CRITICAL();
		me->snake.head.row += row_dir;
		me->snake.head.col += col_dir;
		return HANDLED_STATUS;
	case 'S':
		if (!me->is_s_pwr) {
			me->is_s_pwr = true;
			TimeEvent_disarm(&me->gen_enemy_te);
			TimeEvent_arm(&me->gen_enemy_te, (uint32_t) (me->game_speed * 5),
					(uint32_t) (me->game_speed * 5));
			TimeEvent_arm(&me->rm_s_pwr, configTICK_RATE_HZ * 7U, 0U);
		}
		break;
	case 'D':
		me->d_pwr_factor++;
		TimeEvent_disarm(&me->rm_d_pwr);
		TimeEvent_arm(&me->rm_d_pwr, configTICK_RATE_HZ * 5U, 0U);
		break;
	}
	taskENTER_CRITICAL();
	game_frame[me->snake.head.row][me->snake.head.col] = '*';
	game_frame[me->snake.head.row + row_dir][me->snake.head.col + col_dir] =
			'&';
	game_frame[me->snake.tail.row][me->snake.tail.col] = ' ';
	taskEXIT_CRITICAL();
	me->snake.head.row += row_dir;
	me->snake.head.col += col_dir;
	if (game_frame[me->snake.tail.row][me->snake.tail.col + 1] == '*')
		me->snake.tail.col++;
	else if (game_frame[me->snake.tail.row][me->snake.tail.col - 1] == '*') {
		me->snake.tail.col--;
	} else if (game_frame[me->snake.tail.row + 1][me->snake.tail.col] == '*') {
		me->snake.tail.row++;
	} else {
		me->snake.tail.row--;
	}
	return HANDLED_STATUS;
}
