#include "struct.h"
#include "game_initialization.h"
#include "gamemode.h"


int main(void){
    srand(time(0));
    Grid grid;
    Inventory inventory;
    Difficulty difficulty;
    Mode gamemode;
    Boat fleet[5];

    initialization(&grid, 10, 10, &inventory, &difficulty, &gamemode, fleet);

    run_game(&grid, &inventory, difficulty, gamemode, fleet);

    return 0;

}
