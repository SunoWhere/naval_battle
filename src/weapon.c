#include "weapon.h"

/**
 * Permet d'obtenir le nombre de type d'arme encore disponible
 * @param inventory - Inventaire du joueur
 * @return Retourne le nombre de type d'arme encore disponible
 */
int available_weapon(Inventory inventory){
    return (inventory.artillery != 0)  + (inventory.bomb != 0) + (inventory.tactical != 0) + (inventory.simple_missile != 0);
}

/**
 * Permet d'obtenir la liste des armes encore disponibles dans l'inventaire
 * @param inventory - Inventaire du joueur
 * @param list - Pointeur permettant de récupérer la liste des armes disponibles
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
 * Permet de gérer le cas de l'attaque d'un missile tactique, remplace les caractères composants le bateau par des X, pour
 * signifier sa destruction totale
 * @param grid - Grille de jeu
 * @param boat - Le bateau à détruire
 */
static void tactical_attack_on_boat(Grid *grid, Boat boat){
    for(int i = 0; i < boat.size; i++){
        grid->grid[boat.position[0]][boat.position[1]] = 'X';
        boat.position[0] += (boat.orientation == VERTICAL) ? 1 : 0;
        boat.position[1] += (boat.orientation == HORIZONTAL) ? 1 : 0;
    }
}

/**
 * Permet de savoir si les coordonnées (ligne, colonne) correspondent à des coordonnées possibles dans la grille de jeu
 * @param grid - Grille de jeu
 * @param line - Ligne où l'attaque doit être effectuée
 * @param column - Colonne où l'attaque doit être effectuée
 * @return Retourne 0, si la valeur ne correspond pas à une coordonnée possible dans la grille, retourne 1, dans le cas
 * contraire
 */
int is_in_grid(Grid *grid, short int line, short int column){
    if(line < 0 || line > (grid->height - 1) || column < 0 || column > (grid->width - 1)){
        return 0;
    }else{
        return 1;
    }
}

/**
 * Fonction permettant l'attaque sur la cellule de la grille dont les coordonnées sont passées en paramètres, remplace la
 * cellule touchée par un "O", si l'attque ne touche aucun navire, par un "X", si l'attaque touche une cellule où se situe
 * une des parties d'un des navires
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 * @param line - Ligne ciblée
 * @param column - Colonne ciblée
 * @param is_tactical - Permet de savoir si le missile utilisé est tactique, pour appeler la fonction adéquate
 */
static void attack_on_cell(Grid *grid, Boat *fleet, short int line, short int column, short int is_tactical){
    if(is_in_grid(grid, line, column)){
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
                    if((grid->grid[line][column] != 'X' && grid->grid[line][column] != 'D') && !is_tactical){
                        printf("%c%d has been touched.\n", line + 65, column + 1);
                        boat_touched = 1;
                    }else{
                        printf("%c%d has been already touched.\n", line + 65, column + 1);
                        boat_touched = 1;
                    }
                }
                boat_line += (fleet[i].orientation == VERTICAL) ? 1 : 0;
                boat_column += (fleet[i].orientation == HORIZONTAL) ? 1 : 0;
            }
        }
        grid->grid[line][column] = boat_touched ? 'X' : 'O';
    }
}

/**
 * Permet un tir de missile d'artillerie, ce missile détruit tout ce qui se situe sur la ligne et la colonne ciblées par
 * le joueur, le motif correspond à une croix
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 * @param line - Ligne ciblée par le joueur
 * @param column - Colonne ciblée par le joueur
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
 * Permet une attaque utilisant une bombe, détruit tout ce qui se trouve dans un cercle de rayon de 5 cellules
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 * @param line - Ligne ciblée par le joueur
 * @param column - Colonne ciblée par le joueur
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
 * Permet un tir de missile tactique, ce missile n'attaque qu'une cas mais s'il touche un bateau, le détruit directement
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 * @param line - Ligne ciblée par le joueur
 * @param column - Colonne ciblée par le joueur
 */
void fire_tactical(Grid *grid, Boat *fleet, short int line, short int column){
    attack_on_cell(grid, fleet, line, column, 1);
}

/**
 * Permet un tir de missile simple, attaque uniquement une seule case
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 * @param line - Ligne ciblée par le joueur
 * @param column - Colonne ciblée par le joueur
 */
void fire_simple(Grid *grid, Boat *fleet, short int line, short int column){
    attack_on_cell(grid, fleet, line, column,0);
}