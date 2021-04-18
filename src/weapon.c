#include "weapon.h"

int available_weapon(Inventory inventory){
    return (inventory.artillery != 0)  + (inventory.bomb != 0) + (inventory.tactical != 0) + (inventory.simple_missile != 0);
}

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

void fire_artillery(Grid *grid, Boat *fleet, short int line, short int column){
    for(int i = 0; i < 10; i++){
        if(grid->grid[line][i] == 'B'){
            grid->grid[line][i] = 'X';
        }else if(grid->grid[line][i] == '_'){
            grid->grid[line][i] = 'O';
        }
    }
    for(int i = 0; i < 10; i++){
        if(grid->grid[i][column] == 'B'){
            grid->grid[i][column] = 'X';
        }else if(grid->grid[i][column] == '_'){
            grid->grid[i][column] = 'O';
        }
    }
}

void fire_bomb(Grid *grid, Boat *fleet, short int line, short int column){
    printf("nothing bomb\n");
}

void fire_tactical(Grid *grid, Boat *fleet, short int line, short int column){
    printf("nothing tact\n");
}

void fire_simple(Grid *grid, Boat *fleet, short int line, short int column){
    if(grid->grid[line][column] == 'B'){
        grid->grid[line][column] = 'X';
    }else if(grid->grid[line][column] == '_'){
        grid->grid[line][column] = 'O';
    }
}