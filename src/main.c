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

    if(gamemode == ACTIVE){
        Grid grid_displayed;
        initialize_grid(&grid_displayed, grid.height, grid.width);
        run_game(&grid, &grid_displayed, &inventory, difficulty, gamemode, fleet);
    }else{
        run_game(&grid, NULL, &inventory, difficulty, gamemode, fleet);
    }



    return 0;

}
