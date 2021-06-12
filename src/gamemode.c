#include "gamemode.h"

/**
 * Fonction permettant la libération de la mémoire prise par la grille
 * @param grid - Grille à libérer
 */
static void free_grid(Grid *grid){
    for (int i = 0; i < grid->height; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

/**
 * Copie de la grille de jeu dans la grille de jeu à afficher en mode ACTIVE en remplaçant les éléments d'impacts de la
 * grille de jeu de base par un "_" si la case correspond à un "O"
 * @param grid - Grille de jeu
 * @param grid_displayed - Grille de jeu à afficher en mode ACTIVE
 */
static void active_copy(Grid *grid, Grid *grid_displayed){
    for(int i = 0; i < grid->height; i++){
        for(int j = 0; j < grid->width; ++j) {
            if(grid->grid[i][j] != grid_displayed->grid[i][j]){
                if(grid->grid[i][j] == 'X'){
                    grid_displayed->grid[i][j] = 'X';
                }
                if(grid->grid[i][j] == 'O'){
                    grid_displayed->grid[i][j] = 'O';
                    grid->grid[i][j] = '_';
                }
            }
        }
    }
}

/**
 * Récupère la grille de jeu, le bateau dont on veut connaître le status, les nouvelles coordonnées du bateau et
 * détermine si le bateau et toujours dans la grille de jeu en fonction de la taille du bateau, la taille de grille
 * de jeu et les nouvelles coordonnées du bateau
 * @param grid - Grille de jeu
 * @param boat - Bateau dont on veut tester les nouvelles coordonnées
 * @param line - Nouvelle ligne
 * @param column - Nouvelle colonne
 * @return Retourne 0, si le bateau n'est plus dans la grille, retourne 1, si le bateau est encore dans la grille
 */
static int is_boat_in_grid(Grid *grid, Boat boat, short int line, short int column) {
    for(int i = 0; i < boat.size; i++){
        if(!is_in_grid(grid, line, column)){
            return 0;
        }
        line += boat.orientation == VERTICAL ? 1 : 0;
        column += boat.orientation == HORIZONTAL ? 1 : 0;
    }
    return 1;
}

/**
 * Récupère la chaîne de caractères correspondant au bateau, en fonction de sa position et de sa taille, avec les
 * parties impactées par des missiles remplacés par des "D"
 * @param grid - Grille de jeu
 * @param boat - Bateau à récupérer
 * @param line - Ligne de la grille correspondant à la position de la tête du bateau
 * @param column - Colonne de la grille correspondant à la position de la tête du bateau
 * @param boat_string - Chaîne de caractères qui va permettre stocker la chaîne du bateau
 */
static void get_boat(Grid *grid, Boat boat, short int line, short int column , char *boat_string){
    for(int i = 0; i < boat.size; i++){
        boat_string[i] = (grid->grid[line][column] == 'X' ||  grid->grid[line][column] == 'D') ? 'D' : 'B';
        grid->grid[line][column] = '_';
        line += boat.orientation == VERTICAL ? 1 : 0;
        column += boat.orientation == HORIZONTAL ? 1 : 0;
    }
    boat_string[boat.size] = '\0';
}

/**
 * Fonction permettant l'obtention de l'un index, de manière aléatoire, d'un des bateaux encore en vie
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 * @return Retourne un index valide, donc l'index d'un bateau encore en vie
 */
static short int random_boat_index(Grid *grid, Boat *fleet){
    short int remaining_boat_list[5], list_index = 0;
    for(int i = 0; i < 5; i++){
        if(is_alive(grid, fleet[i])){
            remaining_boat_list[list_index] = i;
            //printf("La valeur de l'index ajouté est %d\n", i);
            list_index++;
        }
    }
    return remaining_boat_list[rand()%list_index];
}

/**
 * Déplace aléatoirement l'un des bateaux restants de la flotte dans la grille de jeu
 * @param grid - Grille de jeu où on va écrire le déplacement
 * @param fleet - Flotte contenant les bateaux ennemis
 */
static void active_move(Grid *grid, Boat *fleet){
    short int index_boat, new_line, new_column, cell_taken, same_position;
    char boat_string[6] = "\0";
    do{
        index_boat = random_boat_index(grid, fleet);
        new_line = fleet[index_boat].orientation == VERTICAL ? fleet[index_boat].position[0] + (rand()%2 ? rand()%3 + 1 : -(rand()%3 + 1)) : fleet[index_boat].position[0];
        new_column = fleet[index_boat].orientation == HORIZONTAL ? fleet[index_boat].position[1] + (rand()%2 ? rand()%3 + 1 : -(rand()%3 + 1)) : fleet[index_boat].position[1];
        cell_taken = is_taken(fleet, index_boat, new_line, new_column);
        same_position = fleet[index_boat].position[0] == new_line && fleet[index_boat].position[1] == new_column;
    }while(cell_taken || !is_alive(grid, fleet[index_boat]) || !is_boat_in_grid(grid, fleet[index_boat], new_line, new_column) || same_position);
    get_boat(grid, fleet[index_boat], fleet[index_boat].position[0], fleet[index_boat].position[1], boat_string);
    fleet[index_boat].position[0] = new_line;
    fleet[index_boat].position[1] = new_column;
    set_boat(grid, fleet[index_boat], boat_string);
    printf("Boat %d has been moved\n", index_boat + 1);
}

/**
 * Appelle l'ensemble des fonctions permettant le bon déroulement de la partie en fonction du mode jeu, et détermine
 * si le joueur à gagner ou non en fonction de s'il reste des bateaux ou non lorsque le joueur n'a plus d'armes, s'il
 * n'y a plus bateau et que le joueur à encore des armes. Après ça, la mémoire des différentes variables est libérée
 * @param grid - Grille de jeu
 * @param grid_displayed_active - Grille de jeu à afficher uniquement en mode ACTIVE
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté de la partie
 * @param gamemode - Mode de jeu de la patie
 * @param fleet - Flotte contenant l'ensemble des bateaux ennemis
 */
void run_game(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty difficulty, Mode gamemode, Boat *fleet){
    while(remaining_boat(grid, fleet) && available_weapon(*inventory)){
        switch (gamemode){
            case CLASSIC:
                show_classic(grid, inventory, difficulty, gamemode, fleet);
                player_menu(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                break;
            case BLIND:
                show_blind(grid, inventory, difficulty, gamemode, fleet);
                player_menu(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                break;
            case ACTIVE:
                show_active(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                player_menu(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
                active_copy(grid, grid_displayed_active);
                active_move(grid, fleet);
                break;
        }
    }
    if(remaining_boat(grid, fleet) > 0){
        printf("You lose !");
    }else{
        printf("You win !");
    }
    free_grid(grid);
    if(gamemode == ACTIVE){
        free_grid(grid_displayed_active);
    }
}