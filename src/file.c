#include "file.h"

/**
 * Fonction servant à la création ou l'actualisation d'un fichier texte pour la persistance des données de la partie
 * actuelle du joueur
 * @param filename - Nom du fichier de sauvegarde (on utilisera save.txt)
 * @param grid - Grille de jeu
 * @param grid_displayed_active - Grille de jeu servant à l'affichage dans le mode ACTIVE
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté actuelle
 * @param gamemode - Mode de jeu actuel
 * @param fleet - Flotte contenant les bateaux ennemis
 */
void save(const char *filename, Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    char *savefile_path = malloc(sizeof(SAVE_DIR) + sizeof(filename)+1);
    strcpy(savefile_path, SAVE_DIR);
    strcat(savefile_path, filename);
    FILE *save = fopen(savefile_path, "w");
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
    if(gamemode == ACTIVE){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                fputc(grid_displayed_active->grid[i][j], save);
            }
            fprintf(save, "\n");
        }
    }
    free(savefile_path);
    fclose(save);
}