#ifndef GAME_H
#define GAME_H

#include "freertos_ao.h"
#include "signals.h"

typedef struct {
	Event super;
	char user_in; // user input
} UserInputEvent;

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
	uint8_t curr_lvl; // current level
	uint8_t max_lvl; // max level
	uint8_t curr_score; // current score
	uint8_t highest_score; // highest score
	uint16_t elapsed_time; // elapsed time sice the start of the game
	uint16_t game_speed;
	Snake snake;
	uint8_t curr_dir; // current direction
	uint8_t d_pwr_factor; // factor for the double score powerup
	uint8_t s_pwr_factor; // factor for the slow down powerup
	TimeEvent gen_apple_te; // Time event to generate an apple symbol
	TimeEvent gen_enemy_te; // Time event to generate an enemy symbol
	TimeEvent gen_pwr_te; // Time event to generate an powerup symbol
	TimeEvent update_time_te; // Time event to update the elapsed time
	TimeEvent update_frame_te; // Time event to update the frame
	uint8_t num_normal_smbl; // number of symbols (apples or enemies)
	uint8_t num_pwr_smbl; // number of powerup symbols
	uint8_t max_pwr_smbl; // max number of powerup symbols
	uint8_t max_total_smbl; // max number of all symbols
} Game;

void Game_ctor(Game *me);

#endif
