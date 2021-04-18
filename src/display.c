#include "display.h"

void show_grid(Grid *grid){
    printf("   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |\n");
    for (int i = 0; i < grid->height; i++) {
        printf(" %c ", 65+i);
        for (int j = 0; j < grid->width; ++j) {
            grid->grid[i][j] == 'B' ? printf("| _ ") : printf("| %c ", grid->grid[i][j]);
        }
        printf(" |\n");
    }
}

void show_grid_debug(Grid *grid){
    printf("   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |\n");
    for (int i = 0; i < grid->height; i++) {
        printf(" %c ", 65+i);
        for (int j = 0; j < grid->width; ++j) {
            printf("| %c ", grid->grid[i][j]);
        }
        printf(" |\n");
    }
}

void show_inventory(Inventory *inventory){
    printf("Inventory :\n"
           "  Artillery missile = %d\n"
           "  Bomb              = %d\n"
           "  Tactical missile  = %d\n"
           "  Simple missile    = %d\n"
           , inventory->artillery, inventory->bomb, inventory->tactical, inventory->simple_missile);
}

char *difficulty_str(Difficulty difficulty){
    switch (difficulty) {
        case EASY:
            return "Easy";
        case MEDIUM:
            return "Medium";
        default:
            return "Hard";
    }
}

char *gamemode_str(Mode gamemode){
    switch (gamemode) {
        case CLASSIC:
            return "Classic";
        case BLIND:
            return "Blind";
        default:
            return "Active";
    }
}

void show_remaining_boat(Grid *grid, Boat *fleet){
    printf("Remaining boat in fleet :\n");
    for(int i = 0; i < 5; i++){
        if(is_alive(grid, fleet[i])){
            printf("  Boat %d : %d hp remaining\n", i+1, remaining_life(grid, fleet[i]));
        }
    }
}