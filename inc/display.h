#ifndef NAVAL_BATTLE_DISPLAY_H
#define NAVAL_BATTLE_DISPLAY_H

#include <stdio.h>
#include "struct.h"
#include "boat.h"

void show_grid(Grid *);
void show_grid_debug(Grid *);
void show_inventory(Inventory *);
char *difficulty_str(Difficulty);
char *gamemode_str(Mode);
void show_remaining_boat(Grid *, Boat *);
void show_classic(Grid *, Inventory *, Difficulty, Mode gamemode, Boat *);

#endif //NAVAL_BATTLE_DISPLAY_H
