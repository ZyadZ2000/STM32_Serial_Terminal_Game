#ifndef GAME_H
#define GAME_H

#include "freertos_ao.h"

typedef static uint32_t (*RandomGenerator)(void);

typedef struct {
	Event super;
	char user_in; // user input
} GameEvent;

typedef struct {
	Active super;
	char * frame;
	char curr_user_in;
	RandomGenerator random;
	uint16_t score;
	uint16_t top_score;
	uint16_t level;
	uint16_t speed;
} Game;

void Game_ctor(Game * me);

#endif
