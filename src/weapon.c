#include "weapon.h"

/**
 *
 * @param inventory
 * @return
 */
int available_weapon(Inventory inventory){
    return (inventory.artillery != 0)  + (inventory.bomb != 0) + (inventory.tactical != 0) + (inventory.simple_missile != 0);
}

/**
 *
 * @param inventory
 * @param list
 */
void available_weapon_list(Inventory *inventory, Weapon *list){
    short int index = 0;
    if(inventory->artillery != 0){
        list[index] = ARTILLERY;
        index++;
    }
    if(inventory->bomb != 0){
        list[index] = BOMB;
        index++;
    }
    if(inventory->tactical != 0){
        list[index] = TACTICAL;
        index++;
    }
    if(inventory->simple_missile != 0){
        list[index] = SIMPLE;
    }
}

/**
 *
 * @param grid
 * @param boat
 */
static void tactical_attack_on_boat(Grid *grid, Boat boat){
    for(int i = 0; i < boat.size; i++){
        grid->grid[boat.position[0]][boat.position[1]] = 'X';
        boat.position[0] += (boat.orientation == VERTICAL) ? 1 : 0;
        boat.position[1] += (boat.orientation == HORIZONTAL) ? 1 : 0;
    }
}

/**
 *
 * @param grid
 * @param line
 * @param column
 * @return
 */
int is_in_grid(Grid *grid, short int line, short int column){
    if(line < 0 || line > (grid->height - 1) || column < 0 || column > (grid->width - 1)){
        return 0;
    }else{
        return 1;
    }
}

/**
 *
 * @param grid
 * @param fleet
 * @param line
 * @param column
 * @param is_tactical
 */
static void attack_on_cell(Grid *grid, Boat *fleet, short int line, short int column, short int is_tactical){
    if(is_in_grid(grid, line, column) && (grid->grid[line][column] != 'X' && grid->grid[line][column] != 'D')){
        short int boat_touched = 0;
        short int boat_line, boat_column;
        for(int i = 0; i < 5; i++){
            boat_line = fleet[i].position[0];
            boat_column = fleet[i].position[1];
            for (int j = 0; j < fleet[i].size && !boat_touched; j++) {
                if(line == boat_line && column == boat_column){
                    if(is_tactical){
                        tactical_attack_on_boat(grid, fleet[i]);
                    }
                    printf("%c%d has been touched.\n", line + 65, column + 1);
                    boat_touched = 1;
                }
                boat_line += (fleet[i].orientation == VERTICAL) ? 1 : 0;
                boat_column += (fleet[i].orientation == HORIZONTAL) ? 1 : 0;
            }
        }
        grid->grid[line][column] = boat_touched ? 'X' : 'O';
    }
}

/**
 *
 * @param grid
 * @param fleet
 * @param line
 * @param column
 */
void fire_artillery(Grid *grid, Boat *fleet, short int line, short int column){
    for(int i = 0; i < 10; i++){
        attack_on_cell(grid, fleet, line, i, 0);
    }
    for(int i = 0; i < 10; i++){
        attack_on_cell(grid, fleet, i, column, 0);
    }
}

/**
 *
 * @param grid
 * @param fleet
 * @param line
 * @param column
 */
void fire_bomb(Grid *grid, Boat *fleet, short int line, short int column){
    for(int i = -2; i < 2; i++){
        attack_on_cell(grid, fleet, line + (int)sqrt(4 - pow(i, 2)), column + i, 0);
        attack_on_cell(grid, fleet, line - (int)sqrt(4 - pow(i, 2)), column - i, 0);
        if(i > -2 && i < 1){
            attack_on_cell(grid, fleet, line + (int)sqrt(1 - pow(i, 2)), column + i, 0);
            attack_on_cell(grid, fleet, line - (int)sqrt(1 - pow(i, 2)), column - i, 0);
        }
    }
    attack_on_cell(grid, fleet, line, column, 0);
}

/**
 *
 * @param grid
 * @param fleet
 * @param line
 * @param column
 */
void fire_tactical(Grid *grid, Boat *fleet, short int line, short int column){
    attack_on_cell(grid, fleet, line, column, 1);
}

/**
 * 
 * @param grid
 * @param fleet
 * @param line
 * @param column
 */
void fire_simple(Grid *grid, Boat *fleet, short int line, short int column){
    attack_on_cell(grid, fleet, line, column,0);
}