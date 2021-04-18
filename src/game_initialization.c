#include "game_initialization.h"

void initialize_grid(Grid *grid, int height, int width){
    grid->height = height;
    grid->width = width;
    grid->boat_array = malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        *(grid->boat_array+i) = malloc(width * sizeof(char));
        memset((grid->boat_array[i]), 95, width * sizeof(char));
    }
}

static void set_inventory(Inventory *inventory, short int artillery, short int bomb, short int tactical, short int simple_missile){
    inventory->artillery = artillery;
    inventory->bomb = bomb;
    inventory->tactical = tactical;
    inventory->simple_missile = simple_missile;
}

void initialize_inventory(Inventory *inventory, Difficulty difficulty){
    switch(difficulty){
        case EASY:
            set_inventory(inventory, 10, 10, 10, 10);
            break;
        case MEDIUM:
            set_inventory(inventory, 3, 5, 5, 10);
            break;
        case HARD:
            set_inventory(inventory, 1, 2, 4, 15);
            break;
        default:
            break;
    }
}

void load_from_file(Grid *grid, Inventory *inventory, Difficulty *difficulty){
    char *line = malloc(12 * sizeof(char));
    FILE *save = fopen("save.txt", "r");
    if(save){
        fscanf(save ,"%d\n%hu %hu %hu %hu\n", difficulty, &(inventory->artillery), &(inventory->bomb), &(inventory->tactical), &(inventory->simple_missile));
        for(int i = 0;(fgets(line, 12 * sizeof(char), save)) != NULL; i++){
            strcpy(grid->boat_array[i], line);
        }
    }else{

    }
    fclose(save);
}
