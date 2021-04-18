#ifndef NAVAL_BATTLE_GAME_INITIALIZATION_H
#define NAVAL_BATTLE_GAME_INITIALIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void initialize_grid(Grid *, int, int);
void initialize_inventory(Inventory *, Difficulty);
void load_from_file(Grid *, Inventory *, Difficulty *);

#endif //NAVAL_BATTLE_GAME_INITIALIZATION_H
