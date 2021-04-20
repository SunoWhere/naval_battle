#include "gamemode.h"

static void free_grid(Grid *grid){
    for (int i = 0; i < grid->height; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

static void active_copy(Grid *grid, Grid *grid_displayed){
    for(int i = 0; i < grid->height; i++){
        for(int j = 0; j < grid->width; ++j) {
            if(grid->grid[i][j] != grid_displayed->grid[i][j]){
                if(grid->grid[i][j] == 'X'){
                    grid_displayed->grid[i][j] = 'X';
                }
                if(grid->grid[i][j] == 'O'){
                    grid_displayed->grid[i][j] = 'O';
                    grid->grid[i][j] = '_';
                }
            }
        }
    }
}

static int is_boat_in_grid(Grid *grid, Boat boat, short int line, short int column) {
    if (is_in_grid(grid, boat.position[0] + line + boat.size * (boat.orientation == VERTICAL), boat.position[1] + column + boat.size * (boat.orientation == HORIZONTAL))) {
        return 1;
    } else {
        return 0;
    }
}

static void get_boat(Grid *grid, Boat boat, short int line, short int column , char *boat_string){
    printf("l=%d, c=%d\n", line, column);
    printf("%d", boat.size);
    for(int i = 0; i < boat.size; i++){
        boat_string[i] = (grid->grid[line][column] == 'X' ||  grid->grid[line][column] == 'D') ? 'D' : 'B';
        grid->grid[line][column] = '_';
        line += boat.orientation == VERTICAL ? 1 : 0;
        column += boat.orientation == HORIZONTAL ? 1 : 0;
        show_grid_debug(grid);
    }
}

static void write_movement_on_grid(Grid *grid, Boat boat, short int previous_line, short int previous_column){
    char boat_string[6];
    get_boat(grid, boat, previous_line, previous_column, boat_string);
    set_boat(grid, boat, boat_string);
    printf("%s\n", boat_string);
}

static void active_move(Grid *grid, Boat *fleet){
    short int index_boat, line_movement, column_movement, cell_taken;
    do{
        index_boat = rand()%5;
        line_movement = rand()%2 ? (rand()%3+1) * (fleet[index_boat].orientation == VERTICAL) : -(rand()%3+1) * (fleet[index_boat].orientation == VERTICAL);
        column_movement = rand()%2 ? (rand()%3+1) * (fleet[index_boat].orientation == HORIZONTAL) : -(rand()%3+1) * (fleet[index_boat].orientation == HORIZONTAL);
        cell_taken = is_taken(fleet, fleet[index_boat], line_movement + fleet[index_boat].position[0], column_movement + fleet[index_boat].position[1]);
        printf("Id boat = %d, L = %d, C = %d, isTaken = %d, isInGrid = %d\n", rand()%5, line_movement + fleet[index_boat].position[0], column_movement + fleet[index_boat].position[1], cell_taken, !is_boat_in_grid(grid, fleet[index_boat], line_movement, column_movement));
    }while(cell_taken || !is_alive(grid, fleet[index_boat]) || !is_boat_in_grid(grid, fleet[index_boat], line_movement, column_movement));
    fleet[index_boat].position[0] += line_movement;
    fleet[index_boat].position[1] += column_movement;
    printf("new l=%d, new c=%d\n", fleet[index_boat].position[0], fleet[index_boat].position[1]);
    write_movement_on_grid(grid, fleet[index_boat], fleet[index_boat].position[0] - line_movement, fleet[index_boat].position[1] - column_movement);
}

void run_game(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    while(remaining_boat(grid, fleet) && available_weapon(*inventory)){
        switch (gamemode){
            case CLASSIC:
                show_classic(grid, inventory, difficulty, gamemode, fleet);
                player_menu(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                break;
            case BLIND:
                show_blind(grid, inventory, difficulty, gamemode, fleet);
                player_menu(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                break;
            case ACTIVE:
                show_active(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                player_menu(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
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
    free_grid(grid);
    if(gamemode == ACTIVE){
        free_grid(grid_displayed_active);
    }
}

