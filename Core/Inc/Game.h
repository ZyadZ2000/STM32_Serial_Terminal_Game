#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "freertos_ao.h"
#include "signals.h"
#include "events.h"

#define SECOND_DIVIDE 20U
#define TIMEOUT configTICK_RATE_HZ / SECOND_DIVIDE   // Every 50 ms

#define LVL1_SPEED 20U
#define LVL2_SPEED 16U
#define LVL3_SPEED 14U
#define LVL4_SPEED 10U
#define LVL5_SPEED 6U

#define APPLE_SMBL 'A'
#define ENEMY_SMBL 'E'
#define MAX_NUM_LVLS 5U
#define NUM_PWR_SMBL 2U
#define FRAME_ROWS 50
#define FRAME_COLS 70

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
//	TimeEvent update_level_te; // Time event to update the level
//	TimeEvent update_dir_te; // Time event to update the direction
//	TimeEvent gen_apple_te;  // Time event to generate an apple symbol
//	TimeEvent gen_enemy_te; // Time event to generate an enemy symbol
//	TimeEvent gen_pwr_te; // Time event to generate a powerup symbol
//	TimeEvent clr_smbl_te; // Time event to clear all symbols
//	TimeEvent rm_d_pwr; //remove the effect of the double score powerup
//	TimeEvent rm_s_pwr; //remove the effect of the slow enemies powerup
	UART_HandleTypeDef *uart;
	uint32_t curr_score; // current score
	uint32_t highest_score; // highest score
	uint32_t elapsed_time; // elapsed time since the start of the game
	uint32_t time_count; //counter for each timeout
	uint32_t d_pwr_time_count;
	uint32_t s_pwr_time_count;
	Snake snake;
	uint16_t game_speed;
	uint8_t curr_lvl; // current level
	uint8_t max_lvl; // max level
	int8_t curr_dir; // current direction
	uint8_t d_pwr_factor; // factor for the double score powerup
	bool is_s_pwr; // boolean for the slow down powerup
} Game;

void Game_ctor(Game *me, UART_HandleTypeDef *uart);

#endif
