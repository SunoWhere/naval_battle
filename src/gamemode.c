#include "gamemode.h"

static void active_copy(Grid *grid, Grid *grid_displayed){
    for(int i = 0; i < grid->height; i++){
        for(int j = 0; j < grid->width; ++j) {
            if(grid->grid[i][j] != grid_displayed->grid[i][j]){
                if(grid->grid[i][j] == 'X'){
                    grid_displayed->grid[i][j] = 'X';
                }
            }
        }
    }
}

static int is_boat_in_grid(Grid *grid, Boat boat, short int line, short int column){
    if(is_in_grid(grid, line, column)){
        if(is_in_grid(grid, line + boat.size * (boat.orientation == VERTICAL), column + boat.size * (boat.orientation == HORIZONTAL))){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

static void write_movement_on_grid(Grid *grid, Boat boat, short int line_movement, short int column_movement){
    if(line_movement > 0 || column_movement > 0){

    }else{

    }
}

static void active_move(Grid *grid, Boat *fleet){
    short int index_boat, line_movement, column_movement, cell_taken;
    do{
        index_boat = rand()%5;
        do{
            line_movement = (rand()%3+1) * (fleet[index_boat].orientation == VERTICAL) * (-1 * rand()%2);
            column_movement = (rand()%3+1) * (fleet[index_boat].orientation == HORIZONTAL) * (-1 * rand()%2);
        }while(!is_boat_in_grid(grid, fleet[index_boat], line_movement, column_movement));
        cell_taken = is_taken(grid, fleet[index_boat], line_movement + fleet[index_boat].position[0], column_movement + fleet[index_boat].position[1]);
    }while(cell_taken);
    write_movement_on_grid(grid, fleet[index_boat], line_movement, column_movement);
    fleet[index_boat].position[0] += line_movement;
    fleet[index_boat].position[1] += column_movement;
}

void run_game(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    while(remaining_boat(grid, fleet) && available_weapon(*inventory)){
        switch (gamemode){
            case CLASSIC:
                show_classic(grid, inventory, difficulty, gamemode, fleet);
                player_menu(grid, inventory, difficulty, gamemode, fleet);
                break;
            case BLIND:
                show_blind(grid, inventory, difficulty, gamemode, fleet);
                player_menu(grid, inventory, difficulty, gamemode, fleet);
                break;
            case ACTIVE:
                show_classic(grid_displayed_active, inventory, difficulty, gamemode, fleet);
                player_menu(grid, inventory, difficulty, gamemode, fleet);
                active_copy(grid, grid_displayed_active);
                active_move(grid, fleet);
                break;
        }
    }
    if(remaining_boat(grid, fleet) > 0){
        printf("You lose !");
    }else{
        printf("You win !");
    }
    free(grid);
    free(grid_displayed_active);
}

