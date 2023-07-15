#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "freertos_ao.h"
#include "signals.h"
#include "events.h"

#define TIMEUNIT_DIV 20U /* Equals 1 second / the game time unit */
#define TIMEOUT configTICK_RATE_HZ / TIMEUNIT_DIV   /* Every 50 ms */

/* game speed in different levels in terms of the number of time units */
#define LVL1_SPEED 20U
#define LVL2_SPEED 16U
#define LVL3_SPEED 14U
#define LVL4_SPEED 10U
#define LVL5_SPEED 6U

#define APPLE_SMBL 'A'
#define ENEMY_SMBL 'E'
#define MAX_NUM_LVLS 5U /* Maximum number of levels of the game */
#define NUM_PWR_SMBL 2U /* number of power-up symbols */
#define FRAME_ROWS 50 /* Number of actual game frame rows inside the game_frame array */
#define FRAME_COLS 70 /* Number of actual game frame cols inside the game_frame array */

typedef struct {
	uint8_t row;
	uint8_t col;
} Position;

typedef struct {
	Position head;
	Position tail;
} Snake;

typedef struct {
	Active super;
	TimeEvent update_time_te; // Time event to update the elapsed time
	UART_HandleTypeDef *uart; // uart handl for receiving user input
	uint32_t curr_score; // current score
	uint32_t highest_score; // highest score
	uint32_t elapsed_time; // elapsed time since the start of the game
	uint32_t time_count; //counter for each timeout
	uint32_t d_pwr_time_count; // time count for the timeout of a "double" power-up
	uint32_t s_pwr_time_count; // time count for the timeout of a "slow enemies" power-up
	Snake snake; // The snake object
	uint16_t game_speed;
	uint8_t curr_lvl; // current level
	uint8_t max_lvl; // max level
	int8_t curr_dir; // current direction
	uint8_t d_pwr_factor; // factor for the double score powerup
	bool is_s_pwr; // boolean for the slow down powerup
} Game;

/* Game constructor */
void Game_ctor(Game *me, UART_HandleTypeDef *uart);

#endif
