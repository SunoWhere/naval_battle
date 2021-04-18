#include "player.h"

static int is_valid_position(char *position, short int *line, short int *column){
    char position_temp[3];
    strcpy(position_temp, position);
    for(int i = 0; i < strlen(position_temp) - 1; ++i){
        position_temp[i] = position_temp[i+1];
    }
    if(position[0] < 'A' || position[0] > 'J'){
        return 0;
    }
    *line = (int)position[0] - 65;
    if(atoi(position_temp) < 1 || atoi(position_temp) > 10){
        return 0;
    }
    *column = atoi(position_temp) - 1;
    return 1;
}

static void position_input(short int *line, short int *column){
    char position[4];
    printf("Please enter the cell position of your strike : (ex: A5)\n");
    fgets(position, 4, stdin);
    while(!is_valid_position(position, line, column)){
        printf("Please enter a valid choice : \n");
        fgets(position, 4, stdin);
    }
}

static void weapon_menu(Grid *grid, Inventory *inventory, Boat *fleet){
    int choice;
    short int line, column;
    Weapon weapon_list[4] = {NONE, NONE, NONE, NONE};
    available_weapon_list(inventory, weapon_list);
    printf("Please select action :\n");
    for(int i = 0; i < available_weapon(*inventory); i++){
        (weapon_list[i] == ARTILLERY) && printf("  %d : Fire artillery missile\n", i + 1);
        (weapon_list[i] == BOMB) && printf("  %d : Fire bomb\n", i + 1);
        (weapon_list[i] == TACTICAL) && printf("  %d : Fire tactical missile\n", i + 1);
        (weapon_list[i] == SIMPLE) && printf("  %d : Fire simple missile\n", i + 1);
    }
    input_choice(&choice, 1, available_weapon(*inventory));
    position_input(&line, &column);
    switch (weapon_list[choice-1]){
        case ARTILLERY:
            fire_artillery(grid, fleet, line, column);
            inventory->artillery -= 1;
            break;
        case BOMB:
            fire_bomb(grid, fleet, line, column);
            inventory->bomb -= 1;
            break;
        case TACTICAL:
            fire_tactical(grid, fleet, line, column);
            inventory->tactical -= 1;
            break;
        default:
            fire_simple(grid, fleet, line, column);
            inventory->simple_missile -= 1;
            break;
    }
}

void player_menu(Grid *grid, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    int choice;
    printf("Please select action :\n  1 : Play\n  2 : Save and quit\n");
    input_choice(&choice, 1, 2);
    switch (choice){
        case 1:
            weapon_menu(grid, inventory, fleet);
            break;
        default:
            save(grid, inventory, difficulty, gamemode, fleet);
            exit(0);
    }
}

