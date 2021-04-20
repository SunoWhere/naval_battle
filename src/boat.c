#include "boat.h"

int remaining_life(Grid *grid, Boat boat){
    short int start_line = boat.position[0], start_column = boat.position[1];
    short int life = boat.size;
    while((boat.orientation == VERTICAL && boat.position[0] - start_line < boat.size) || (boat.orientation == HORIZONTAL && (boat.position[1] - start_column < boat.size))){
        if(grid->grid[boat.position[0]][boat.position[1]] == 'X' || grid->grid[boat.position[0]][boat.position[1]] == 'D'){
            life -= 1;
        }
        boat.position[0] += (boat.orientation == VERTICAL) ? 1 : 0;
        boat.position[1] += (boat.orientation == HORIZONTAL) ? 1 : 0;
    }
    return life;
}

int is_alive(Grid *grid, Boat boat){
    return remaining_life(grid, boat) ? 1 : 0;
}

int remaining_boat(Grid *grid, Boat *fleet){
    short int boat = 0;
    for (int i = 0; i < 5; i++) {
        boat += is_alive(grid, fleet[i]);
    }
    return boat;
}