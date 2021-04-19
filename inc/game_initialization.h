#ifndef NAVAL_BATTLE_GAME_INITIALIZATION_H
#define NAVAL_BATTLE_GAME_INITIALIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include "struct.h"
#include "stdjm.h"

void initialize_grid(Grid *, short int, short int);
int is_taken(Grid *, Boat, short int, short int);
void load(const char *, Grid *, Inventory *, Difficulty *, Mode *, Boat *);
void initialization(Grid *, short int, short int, Inventory *, Difficulty *, Mode *, Boat *);

#endif //NAVAL_BATTLE_GAME_INITIALIZATION_H
