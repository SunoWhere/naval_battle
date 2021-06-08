#include "display.h"

/**
 * Affiche la grille de jeu avec les bateaux dissimulés et les marqueurs liés aux impacts
 * @param grid - La grille de Jeu
 */
void show_grid(Grid *grid){
    printf("   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |\n");
    for (int i = 0; i < grid->height; i++) {
        printf(" %c ", 65+i);
        for (int j = 0; j < grid->width; ++j) {
            grid->grid[i][j] == 'B' || grid->grid[i][j] == 'D' ? printf("| _ ") : printf("| %c ", grid->grid[i][j]);
        }
        printf(" |\n");
    }
    printf("\n");
}

/*void show_grid_debug(Grid *grid){
    printf("   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |\n");
    for (int i = 0; i < grid->height; i++) {
        printf(" %c ", 65+i);
        for (int j = 0; j < grid->width; ++j) {
            printf("| %c ", grid->grid[i][j]);
        }
        printf(" |\n");
    }
    printf("\n");
}*/

/**
 * Affiche l'inventaire du joueur avec la quantité restante de chaque arme
 * @param inventory - Inventaire du joueur
 */
void show_inventory(Inventory *inventory){
    printf("Inventory :\n"
           "  Artillery missile = %d\n"
           "  Bomb              = %d\n"
           "  Tactical missile  = %d\n"
           "  Simple missile    = %d\n\n"
           , inventory->artillery, inventory->bomb, inventory->tactical, inventory->simple_missile);
}

/**
 * Récupère la difficulté (la valeur en tant qu'énumération de type Difficulty)
 * @param difficulty - Difficulté actuelle
 * @return Retourne la difficulté sour la forme d'une chaîne de charactères
 */
char *difficulty_str(Difficulty difficulty){
    switch (difficulty) {
        case EASY:
            return "Easy";
        case MEDIUM:
            return "Medium";
        default:
            return "Hard";
    }
}

/**
 * Récupère le mode de jeu (la valeur en tant qu'énumération de type Mode)
 * @param gamemode - Mode de jeu actuel
 * @return Retourne le mode de jeu sour la forme d'une chaîne de charactères
 */
char *gamemode_str(Mode gamemode){
    switch (gamemode) {
        case CLASSIC:
            return "Classic";
        case BLIND:
            return "Blind";
        default:
            return "Active";
    }
}

/**
 * Affiche la liste des bateaux restant avec leur point de vie respectif
 * @param grid - Grille de jeu
 * @param fleet - Flotte de bateaux dont on veut afficher le status
 */
void show_remaining_boat(Grid *grid, Boat *fleet){
    printf("Remaining boat in fleet : %d\n", remaining_boat(grid, fleet));
    for(int i = 0; i < 5; i++){
        if(is_alive(grid, fleet[i])){
            printf("  Boat %d : %d/%d hp remaining\n", i+1, remaining_life(grid, fleet[i]), fleet[i].size);
        }
    }
    printf("\n");
}

/**
 * Affiche la difficulté et le mode jeu actuelle à partir des valeurs des énum en paramètre, le nom de la difficulté et
 * du mode de jeu sont récupérés grâce aux fonction difficulty_str et gamemode_str()
 * @param difficulty - Difficulté actuelle
 * @param gamemode - Mode de jeu actuel
 */
void show_difficulty_gamemode(Difficulty difficulty, Mode gamemode){
    printf("Difficulty = %s, Gamemode = %s\n", difficulty_str(difficulty), gamemode_str(gamemode));
    printf("\n");
}

/**
 * Appelle les fonctions utiles à l'affichage du mode CLASSIC
 * @param grid - Grille de jeu
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté actuelle
 * @param gamemode - Mode de jeu actuel
 * @param fleet - Flotte contenant les bateaux ennemis
 */
void show_classic(Grid *grid, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    show_difficulty_gamemode(difficulty, gamemode);
    show_grid(grid);
    show_inventory(inventory);
    show_remaining_boat(grid, fleet);
}

/**
 * Appelle les fonctions utiles à l'affichage du mode BLIND
 * @param grid - Grille de jeu (la grille n'est pas affichée mais nécessaire pour les autres fonctions)
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté actuelle
 * @param gamemode - Mode de jeu actuel
 * @param fleet - Flotte contenant les bateaux ennemis
 */
void show_blind(Grid *grid, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    show_difficulty_gamemode(difficulty, gamemode);
    show_inventory(inventory);
    show_remaining_boat(grid, fleet);
}

/**
 * Appelle les fonctions utiles à l'affichage du mode ACTIVE
 * @param grid - Grille de jeu (cette grille n'est pas affichée mais contient des informations importantes)
 * @param grid_displayed_active - Grille de jeu à afficher (cette grille est affichée et contient uniquement les
 * informations nécessaire pour l'affichage)
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté actuelle
 * @param gamemode - Mode de jeu actuel
 * @param fleet - Flotte contenant les bateaux ennemis
 */
void show_active(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    show_difficulty_gamemode(difficulty, gamemode);
    show_grid(grid_displayed_active);
    show_inventory(inventory);
    show_remaining_boat(grid, fleet);
}