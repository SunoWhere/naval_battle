#ifndef NAVAL_BATTLE_GAMEMODE_H
#define NAVAL_BATTLE_GAMEMODE_H

#include <time.h>
#include "struct.h"
#include "display.h"
#include "player.h"
#include "game_initialization.h"
#include "weapon.h"
#include "boat.h"

void run_game(Grid *, Grid *, Inventory *, Difficulty, Mode, Boat *);

#endif //NAVAL_BATTLE_GAMEMODE_H
