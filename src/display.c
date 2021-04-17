#include "display.h"

void show_grid(Grid *grid){
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; ++j) {
            printf("%c ", grid->boat_array[i][j]);
        }
        printf("\n");
    }
}

void show_inventory(Inventory *inventory){
    printf("Inventory :\n"
           "\tArtillery missile = %d\n"
           "\tBomb              = %d\n"
           "\tTactical missile  = %d\n"
           "\tSimple missile    = %d\n", inventory->artillery, inventory->bomb, inventory->tactical, inventory->simple_missile);
}