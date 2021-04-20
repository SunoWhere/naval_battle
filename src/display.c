#include "display.h"

void show_grid(Grid *grid){
    printf("   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |\n");
    for (int i = 0; i < grid->height; i++) {
        printf(" %c ", 65+i);
        for (int j = 0; j < grid->width; ++j) {
            grid->grid[i][j] == 'B' || grid->grid[i][j] == 'D' ? printf("| _ ") : printf("| %c ", grid->grid[i][j]);
        }
        printf(" |\n");
    }
    printf("\n");
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
    printf("\n");
}

void show_inventory(Inventory *inventory){
    printf("Inventory :\n"
           "  Artillery missile = %d\n"
           "  Bomb              = %d\n"
           "  Tactical missile  = %d\n"
           "  Simple missile    = %d\n\n"
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
    printf("Remaining boat in fleet : %d\n", remaining_boat(grid, fleet));
    for(int i = 0; i < 5; i++){
        if(is_alive(grid, fleet[i])){
            printf("  Boat %d : %d/%d hp remaining\n", i+1, remaining_life(grid, fleet[i]), fleet[i].size);
        }
    }
    printf("\n");
}

void show_difficulty_gamemode(Difficulty difficulty, Mode gamemode){
    printf("Difficulty = %s, Gamemode = %s\n", difficulty_str(difficulty), gamemode_str(gamemode));
    printf("\n");
}

void show_classic(Grid *grid, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    show_difficulty_gamemode(difficulty, gamemode);
    show_grid(grid);
    show_grid_debug(grid);
    show_inventory(inventory);
    show_remaining_boat(grid, fleet);
}

void show_blind(Grid *grid, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    show_difficulty_gamemode(difficulty, gamemode);
    show_inventory(inventory);
    show_remaining_boat(grid, fleet);
}

void show_active(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    show_difficulty_gamemode(difficulty, gamemode);
    show_grid(grid_displayed_active);
    show_grid_debug(grid);
    show_inventory(inventory);
    show_remaining_boat(grid, fleet);
}