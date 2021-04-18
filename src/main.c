#include "struct.h"
#include "game_initialization.h"
#include "display.h"
#include "stdjm.h"
#include "file.h"


int main(void){
    srand(time(0));
    Grid grid;
    Inventory inventory;
    Difficulty difficulty;
    Mode gamemode;
    Boat fleet[5];

    initialization(&grid, 10, 10, &inventory, &difficulty, &gamemode, fleet);
    show_grid(&grid);
    printf("Difficulty = %s, Gamemode = %s\n", difficulty_str(difficulty), gamemode_str(gamemode));
    show_inventory(&inventory);
    show_remaining_boat(&grid, fleet);
    save(&grid, &inventory, difficulty, gamemode, fleet);

    return 0;

}
