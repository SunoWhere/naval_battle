#ifndef NAVAL_BATTLE_WEAPON_H
#define NAVAL_BATTLE_WEAPON_H

#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

int available_weapon(Inventory);
void available_weapon_list(Inventory *, Weapon *);
void fire_artillery(Grid *, Boat *, short int, short int);
void fire_bomb(Grid *, Boat *, short int, short int);
void fire_tactical(Grid *, Boat *, short int, short int);
void fire_simple(Grid *, Boat *, short int, short int);

#endif //NAVAL_BATTLE_WEAPON_H
