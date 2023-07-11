#ifndef GAME_H
#define GAME_H

#include "freertos_ao.h"
#include "signals.h"
#include "events.h"

#define LVL1_SPD configTICK_RATE_HZ
#define LVL2_SPD configTICK_RATE_HZ - 150U
#define LVL3_SPD configTICK_RATE_HZ - 300U
#define LVL4_SPD configTICK_RATE_HZ - 450U
#define LVL5_SPD configTICK_RATE_HZ - 600U
#define LVL6_SPD configTICK_RATE_HZ - 750U

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
	int8_t curr_dir; // current direction
	uint8_t d_pwr_factor; // factor for the double score powerup
	uint8_t s_pwr_factor; // factor for the slow down powerup
	TimeEvent update_time_te; // Time event to update the elapsed time
	TimeEvent update_frame_te; // Time event to update the frame
	TimeEvent update_level_te; // Time event to update the frame
	TimeEvent gen_apple_te; // Time event to generate an apple symbol
	TimeEvent gen_enemy_te; // Time event to generate an enemy symbol
	TimeEvent gen_pwr_te; // Time event to generate an powerup symbol
	TimeEvent clr_pwr_te; // Time event to clear all powerup symbols
	TimeEvent rm_d_pwr; //remove the effect of the double score powerup
	TimeEvent rm_s_pwr; //remove the effect of the slow down powerup
	uint8_t num_normal_smbl; // number of symbols (apples or enemies)
	uint8_t num_pwr_smbl; // number of powerup symbols
	uint8_t max_pwr_smbl; // max number of powerup symbols
	uint8_t max_total_smbl; // max number of all symbols
} Game;

void Game_ctor(Game *me);

#endif
