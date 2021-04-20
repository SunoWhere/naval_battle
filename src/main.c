#include "struct.h"
#include "game_initialization.h"
#include "gamemode.h"


int main(void){
    srand(time(0));
    Grid grid;
    Grid grid_displayed;
    Inventory inventory;
    Difficulty difficulty;
    Mode gamemode;
    Boat fleet[5];

    initialization(&grid, &grid_displayed, 10, 10, &inventory, &difficulty, &gamemode, fleet);

    run_game(&grid, &grid_displayed, &inventory, difficulty, gamemode, fleet);

    return 0;

}
