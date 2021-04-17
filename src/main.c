#include <stdio.h>
#include "struct.h"
#include "game_initialization.h"
#include "display.h"


int main() {

    Grid grid;
    initialize_grid(&grid, 10, 10);

    Inventory inventory;
    initialize_inventory(&inventory, HARD);

    show_inventory(&inventory);

    return 0;

}
