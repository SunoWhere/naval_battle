#include "boat.h"

/**
 *Récupère la grille et le bateau dont on veut connaître le nombre de point de vie restant
 * @param grid - La grille de jeu
 * @param boat - Le bateau à analyser
 * @return Retourne le nombre de point restant pour le bateau
 */
int remaining_life(Grid *grid, Boat boat){
    short int start_line = boat.position[0], start_column = boat.position[1];
    short int life = boat.size;
    while((boat.orientation == VERTICAL && boat.position[0] - start_line < boat.size) || (boat.orientation == HORIZONTAL && (boat.position[1] - start_column < boat.size))){
        if(grid->grid[boat.position[0]][boat.position[1]] == 'X' || grid->grid[boat.position[0]][boat.position[1]] == 'D'){
            life -= 1;
        }
        boat.position[0] += (boat.orientation == VERTICAL) ? 1 : 0;
        boat.position[1] += (boat.orientation == HORIZONTAL) ? 1 : 0;
    }
    return life;
}

/**
 *Récupère la grille et le bateau dont on veut connaître le status
 * @param grid - La grille de jeu
 * @param boat - Le bateau à analyser
 * @return Retourne l'état du bateau (en vie ou non)
 */
int is_alive(Grid *grid, Boat boat){
    return remaining_life(grid, boat) ? 1 : 0;
}

/**
 *Récupère la grille et la flotte de bateaux
 * @param grid - La grille de jeu
 * @param fleet - La flotte contenant l'ensemble des bateaux
 * @return Retourne le nombre de bateau restant à éliminer
 */
int remaining_boat(Grid *grid, Boat *fleet){
    short int boat = 0;
    for (int i = 0; i < 5; i++) {
        boat += is_alive(grid, fleet[i]);
    }
    return boat;
}