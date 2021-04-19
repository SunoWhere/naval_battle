#include "struct.h"
#include "game_initialization.h"
#include "display.h"
#include "boat.h"
#include "weapon.h"
#include "player.h"


int main(void){
    srand(time(0));
    Grid grid;
    Inventory inventory;
    Difficulty difficulty;
    Mode gamemode;
    Boat fleet[5];

    initialization(&grid, 10, 10, &inventory, &difficulty, &gamemode, fleet);

    while(remaining_boat(&grid, fleet) && available_weapon(inventory)){
        show_classic(&grid, &inventory, difficulty, gamemode, fleet);
        player_menu(&grid, &inventory, difficulty, gamemode, fleet);
    }

    return 0;

}
