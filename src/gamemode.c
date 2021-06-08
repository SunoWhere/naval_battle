#include "gamemode.h"

/**
 *
 * @param grid
 */
static void free_grid(Grid *grid){
    for (int i = 0; i < grid->height; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

/**
 *
 * @param grid
 * @param grid_displayed
 */
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

/**
 *
 * @param grid
 * @param boat
 * @param line
 * @param column
 * @return
 */
static int is_boat_in_grid(Grid *grid, Boat boat, short int line, short int column) {
    for(int i = 0; i < boat.size; i++){
        if(!is_in_grid(grid, line, column)){
            return 0;
        }
        line += boat.orientation == VERTICAL ? 1 : 0;
        column += boat.orientation == HORIZONTAL ? 1 : 0;
    }
    return 1;
}

/**
 *
 * @param grid
 * @param boat
 * @param line
 * @param column
 * @param boat_string
 */
static void get_boat(Grid *grid, Boat boat, short int line, short int column , char *boat_string){
    for(int i = 0; i < boat.size; i++){
        boat_string[i] = (grid->grid[line][column] == 'X' ||  grid->grid[line][column] == 'D') ? 'D' : 'B';
        grid->grid[line][column] = '_';
        line += boat.orientation == VERTICAL ? 1 : 0;
        column += boat.orientation == HORIZONTAL ? 1 : 0;
    }
    boat_string[boat.size] = '\0';
}

/**
 *
 * @param grid
 * @param fleet
 */
static void active_move(Grid *grid, Boat *fleet){
    short int index_boat, new_line, new_column, cell_taken, same_position;
    char boat_string[6] = "\0";
    do{
        index_boat = rand()%5;
        new_line = fleet[index_boat].orientation == VERTICAL ? fleet[index_boat].position[0] + (rand()%2 ? rand()%3 + 1 : -(rand()%3 + 1)) : fleet[index_boat].position[0];
        new_column = fleet[index_boat].orientation == HORIZONTAL ? fleet[index_boat].position[1] + (rand()%2 ? rand()%3 + 1 : -(rand()%3 + 1)) : fleet[index_boat].position[1];
        cell_taken = is_taken(fleet, index_boat, new_line, new_column);
        same_position = fleet[index_boat].position[0] == new_line && fleet[index_boat].position[1] == new_column;
    }while(cell_taken || !is_alive(grid, fleet[index_boat]) || !is_boat_in_grid(grid, fleet[index_boat], new_line, new_column) || same_position);
    get_boat(grid, fleet[index_boat], fleet[index_boat].position[0], fleet[index_boat].position[1], boat_string);
    fleet[index_boat].position[0] = new_line;
    fleet[index_boat].position[1] = new_column;
    set_boat(grid, fleet[index_boat], boat_string);
    printf("Boat %d has been moved\n", index_boat + 1);
}

/**
 *
 * @param grid
 * @param grid_displayed_active
 * @param inventory
 * @param difficulty
 * @param gamemode
 * @param fleet
 */
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