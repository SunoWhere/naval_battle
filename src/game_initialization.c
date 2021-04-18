#include "game_initialization.h"

static void initialize_grid(Grid *grid, int height, int width){
    grid->height = height;
    grid->width = width;
    grid->grid = malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        *(grid->grid+i) = malloc(width * sizeof(char));
        memset((grid->grid[i]), 95, width * sizeof(char));
    }
}

static void set_inventory(Inventory *inventory, short int artillery, short int bomb, short int tactical, short int simple_missile){
    inventory->artillery = artillery;
    inventory->bomb = bomb;
    inventory->tactical = tactical;
    inventory->simple_missile = simple_missile;
}

static void initialize_inventory(Inventory *inventory, Difficulty difficulty){
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

static void initialiaze_fleet(Boat *fleet){
    for(int i = 0; i < 5; i++){
        fleet[i].size = i < 2 ? i + 2 : i + 1;
        fleet[i].orientation = rand()%2;
    }
}

static void set_difficulty(Difficulty *difficulty){
    int choice = 0;
    printf("Chose difficulty :\n  1 : Easy\n  2 : Medium\n  3 : Hard\n");
    input_choice(&choice, 1, 3);
    *difficulty = choice - 1;
}

static void set_gamemode(Mode *gamemode){
    int choice = 0;
    printf("Chose gamemode:\n  1 : Classic\n  2 : Blind\n  3 : Active\n");
    input_choice(&choice, 1, 3);
    *gamemode = choice - 1;
}

static void new_game(Inventory *inventory, Difficulty *difficulty, Mode *gamemode){
    set_difficulty(difficulty);
    set_gamemode(gamemode);
    initialize_inventory(inventory, *difficulty);
}

static void load(Grid *grid, Inventory *inventory, Difficulty *difficulty, Mode *gamemode){
    char *line = malloc(12 * sizeof(char));
    FILE *save = fopen("save.txt", "r");
    if(save){
        fscanf(save ,"%d\n%d\n%hu %hu %hu %hu\n", difficulty, gamemode, &(inventory->artillery), &(inventory->bomb), &(inventory->tactical), &(inventory->simple_missile));
        for(int i = 0;(fgets(line, 12 * sizeof(char), save)) != NULL; i++){
            strcpy(grid->grid[i], line);
        }
    }else{
        printf("No save file found, a new game will start.\n");
        new_game(inventory, difficulty, gamemode);
    }
    free(line);
    fclose(save);
}

void initialization(Grid *grid, short int height, short int width, Inventory *inventory, Difficulty *difficulty, Mode *gamemode, Boat *fleet){
    int choice = 0;
    initialize_grid(grid, height, width);
    printf("Welcome to Naval Battle : enHanced edition\n");
    printf("Do you want to :\n  1 : Start a new game\n  2 : Resume the previous game\n  3 : Exit game\n");
    input_choice(&choice, 1, 3);
    switch(choice){
        case 1:
            new_game(inventory, difficulty, gamemode);
            break;
        case 2:
            load(grid, inventory, difficulty, gamemode);
            break;
        default:
            exit(0);
    }
}