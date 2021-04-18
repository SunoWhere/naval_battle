#include "struct.h"
#include "game_initialization.h"
#include "display.h"
#include "stdjm.h"


int main(void){

    Grid grid;
    Inventory inventory;
    Difficulty difficulty;
    Mode gamemode;
    Boat fleet[5];

    initialization(&grid, 10, 10, &inventory, &difficulty, &gamemode);
    show_grid(&grid);
    show_inventory(&inventory);
    printf("D = %d, G = %d", difficulty, gamemode);

    return 0;

}
