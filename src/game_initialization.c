#include "game_initialization.h"

void initialize_grid(Grid *grid, height, width){
    grid->height = height;
    grid->width = width;
    grid->boat_array = malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        *(grid->boat_array+i) = malloc(width * sizeof(char));
        memset((grid->boat_array+i), 95, width * sizeof(char));
    }
}
