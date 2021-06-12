#include "player.h"

/**
 * Teste la validité d'une position entrée, vérifie si le format entré correspond au format attendu, et que la valeur
 * soit une valeur possible
 * @param position - La chaîne de caractères correspond à la position entrée par l'utilisateur dont on veut tester la
 * validité
 * @param line - La ligne de la position, ce pointeur permet de modifier directement la valeur de la ligne
 * @param column - La colonne de la position, ce pointeur permet de modifier directement la valeur de la coordonnée
 * @return
 */
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

/**
 * Fonction permettant la saisie de la position par l'utilisateur
 * @param line - Pointeur permettant de modifier directement la valeur de la ligne
 * @param column - Pointeur permettant de modifier directement la valeur de la colonne
 */
static void position_input(short int *line, short int *column){
    char position[4];
    printf("Please enter the cell position of your strike : (ex: A5)\n");
    fgets(position, 4, stdin);
    while(!is_valid_position(position, line, column)){
        printf("Please enter a valid choice : \n");
        fgets(position, 4, stdin);
    }
}

/**
 * Affiche le menu des armes permettant de sélectionner l'arme à utiliser pour attaquer
 * @param grid - La grille de jeu
 * @param inventory - L'inventaire du joueur
 * @param fleet - La flotte contenant les bateaux ennemis
 */
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

/**
 * Affiche le menu du joueur, lui permettant de choisir entre le fait d'effectuer une action, donc ouvrir le menu des
 * armes ou de arrêter la partie et la sauvegarder
 * @param grid - Grille de jeu
 * @param grid_displayed_active -  Grille de jeu servant uniquement à l'affichage en mode ACTIVE
 * @param inventory - L'inventaire du joueur
 * @param difficulty - La difficulté de la partie actuelle
 * @param gamemode - Le mode de jeu actuel
 * @param fleet - La flotte contenant les bateaux ennemis
 */
void player_menu(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    int choice;
    printf("Please select action :\n  1 : Play\n  2 : Save and quit\n");
    input_choice(&choice, 1, 2);
    switch (choice){
        case 1:
            weapon_menu(grid, inventory, fleet);
            break;
        default:
            save("save.txt", grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
            exit(0);
    }
}

