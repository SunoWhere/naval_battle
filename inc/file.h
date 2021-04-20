#ifndef NAVAL_BATTLE_FILE_H
#define NAVAL_BATTLE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

void save(const char *, Grid *, Grid *, Inventory *, Difficulty, Mode, Boat *);

#endif //NAVAL_BATTLE_FILE_H
