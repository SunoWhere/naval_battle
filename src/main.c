#include "struct.h"
#include "game_initialization.h"
#include "display.h"


int main() {

    Difficulty difficulty = HARD;

    Grid grid;
    initialize_grid(&grid, 10, 10);

    Inventory inventory;
    initialize_inventory(&inventory, difficulty);


    load_from_file(&grid, &inventory, &difficulty);
    show_grid(&grid);
    show_inventory(&inventory);
    printf("%d", difficulty);

    return 0;

}
