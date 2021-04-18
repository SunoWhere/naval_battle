#include "file.h"

void save(Grid *grid, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    FILE *save = fopen("save.txt", "w");
    fprintf(save, "Difficulty=%d\nGamemode=%d\n", difficulty, gamemode);
    fprintf(save, "Artillery=%hu Bomb=%hu Tactical=%hu Simple=%hu\n", inventory->artillery, inventory->bomb, inventory->tactical, inventory->simple_missile);
    for(int i = 0; i < 5; i++){
        fprintf(save, "B=%hu,%hu,%d\n", fleet[i].position[0], fleet[i].position[1], fleet[i].orientation);
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            fputc(grid->grid[i][j], save);
        }
        fprintf(save, "\n");
    }
}