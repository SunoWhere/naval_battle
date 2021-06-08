#include "game_initialization.h"

/**
 * Initialise les structures de type Grid dont la taille (hauteur et largeur) est définie en paramètre, la grille est
 * un tableau de chaînes de charactères, le charatère de base, remplissant les chaînes, est le charactère "_"
 * @param  - Grille à initialiser (structure de type Grid)
 * @param height - Hauteur de la grille
 * @param width - Largeur de la grille
 */
void initialize_grid(Grid *grid, short int height, short int width){
    grid->height = height;
    grid->width = width;
    grid->grid = malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        *(grid->grid+i) = malloc(width * sizeof(char));
        memset((grid->grid[i]), 95, width * sizeof(char));
    }
}

/**
 * Définit la quantité de chaque arme de l'inventaire du joueur en fonction des paramètres donnés
 * @param inventory - Inventaire du joueur
 * @param artillery - Quantité de missiles d'artillerie à initialiser
 * @param bomb - Quantité de bombes à initialiser
 * @param tactical - Quantité de missiles tactiques à initialiser
 * @param simple_missile - Quantité de missiles simples à initialiser
 */
static void set_inventory(Inventory *inventory, short int artillery, short int bomb, short int tactical, short int simple_missile){
    inventory->artillery = artillery;
    inventory->bomb = bomb;
    inventory->tactical = tactical;
    inventory->simple_missile = simple_missile;
}

/**
 * Initialise l'inventaire en fonction de la difficulté qui a été choisie pour la partie
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté actuelle
 */
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

/**
 * Initialise la flotte de bateaux, les bateaux ont différentes tailles (Taille : 2, 3, 3, 4, 5) et l'orientation du
 * bateau est générée de manière aléatoire (soit verticale, soit horizontale)
 * @param fleet - Flotte contenant les bateaux ennemis
 */
static void initialize_fleet(Boat *fleet){
    for(int i = 0; i < 5; i++){
        fleet[i].size = i < 2 ? i + 2 : i + 1;
        fleet[i].orientation = rand()%2;
    }
}

/**
 * Récupère la flotte, l'index du bateau dans la flotte, les coordonnées du bateau, et détermine si les coordonnées
 * correspondent à un emplacement libre en fonction de la taille du bateau et des coordonnées des autres bateaux
 * définis dans la flotte et de leur taille
 * @param fleet - Flotte contenant les bateaux ennemis
 * @param boat_index - Index du bateau dans la flotte
 * @param line - Ligne de la grille sélectionnée
 * @param column - Colonne de la grille sélectionnée
 * @return Retourne 1, si le bateau se supperpose sur un autre bateau de la flotte, retourne 0, si le bateau ne se
 * supperpose à aucun bateau de la flotte et peut donc être placé
 */
int is_taken(Boat *fleet, short int boat_index, short int line, short int column){
    short int boat_start_line = line, boat_start_column = column;
    short int fleet_boat_line, fleet_boat_column;
    for(int i = 0; i < 5; i++){
        line = boat_start_line;
        column = boat_start_column;
        if(boat_index != i){
            for(int j = 0; j < fleet[boat_index].size; j++) {
                fleet_boat_line = fleet[i].position[0];
                fleet_boat_column = fleet[i].position[1];
                for(int k = 0; k < fleet[i].size; k++) {
                    if(line == fleet_boat_line && column == fleet_boat_column){
                        return 1;
                    }
                    fleet_boat_line += (fleet[i].orientation == VERTICAL) ? 1 : 0;
                    fleet_boat_column += (fleet[i].orientation == HORIZONTAL) ? 1 : 0;
                }
                line += (fleet[boat_index].orientation == VERTICAL) ? 1 : 0;
                column += (fleet[boat_index].orientation == HORIZONTAL) ? 1 : 0;
            }
        }
    }
    return 0;
}

/**
 * Place le bateau dans la grille sous forme d'une chaîne de charactère
 * @param grid - Grille de jeu
 * @param boat - Bateau à placer
 * @param boat_representation - Chaîne de charactères correspondant à la manière dont sera écrit le bateau sur la grile
 */
void set_boat(Grid *grid, Boat boat, char *boat_representation){
    short int line = boat.position[0], column = boat.position[1];
    for(int i = 0; i < boat.size; i++){
        grid->grid[line][column] = boat_representation[i];
        line += (boat.orientation == VERTICAL) ? 1 : 0;
        column += (boat.orientation == HORIZONTAL) ? 1 : 0;
    }
}

/**
 * Appelle la fonction d'initialisation de la flotte et place les bateaux dans la grille, les coordonnées sont générées
 * de manière procédurale, ce n'est pas purement aléatoire car il y a des contraintes liées à la taille de la grille,
 * la taille du bateau, et l'orientation
 * @param grid - Grille de jeu
 * @param fleet - Flotte contenant les bateaux ennemis
 */
static void set_fleet(Grid *grid, Boat *fleet){
    initialize_fleet(fleet);
    short int line, column;
    for(int i = 4; i >=0 ; i--){
        do{
            line = rand()%(grid->height - (fleet[i].size * (fleet[i].orientation == VERTICAL)));
            column = rand()%(grid->width - (fleet[i].size * (fleet[i].orientation == HORIZONTAL)));
        }while(is_taken(fleet, i, line, column));
        fleet[i].position[0] = line;
        fleet[i].position[1] = column;
        set_boat(grid, fleet[i], "BBBBB");
    }
}

/**
 * Permet au joueur de définir la difficulté du jeu
 * @param difficulty - Difficulté du jeu à définir
 */
static void set_difficulty(Difficulty *difficulty){
    int choice = 0;
    printf("Chose difficulty :\n  1 : Easy\n  2 : Medium\n  3 : Hard\n");
    input_choice(&choice, 1, 3);
    *difficulty = choice - 1;
}

/**
 * Permet au joueur de définir le mode de jeu
 * @param gamemode - Mode de jeu à définir
 */
static void set_gamemode(Mode *gamemode){
    int choice = 0;
    printf("Chose gamemode:\n  1 : Classic\n  2 : Blind\n  3 : Active\n");
    input_choice(&choice, 1, 3);
    *gamemode = choice - 1;
}

/**
 * Appelle les différentes fonctions relatives à la création d'une nouvelle partie
 * @param grid - Grille de jeu
 * @param grid_displayed_active - Grille de jeu à afficher dans le cas où le joueur joue en mode ACTIVE
 * @param inventory - Inventaire du joueur
 * @param difficulty - Difficulté de la partie
 * @param gamemode - Mode de jeu
 * @param fleet - Flotte qui va contenir l'ensemble des bateaux ennemis
 */
static void new_game(Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty *difficulty, Mode *gamemode, Boat *fleet){
    set_difficulty(difficulty);
    set_gamemode(gamemode);
    if(*gamemode == ACTIVE){
        initialize_grid(grid_displayed_active, grid->height, grid->width);
    }
    initialize_inventory(inventory, *difficulty);
    set_fleet(grid, fleet);
}

/**
 *
 * @param filename
 * @param grid
 * @param grid_displayed_active
 * @param inventory
 * @param difficulty
 * @param gamemode
 * @param fleet
 */
void load(const char *filename, Grid *grid, Grid *grid_displayed_active, Inventory *inventory, Difficulty *difficulty, Mode *gamemode, Boat *fleet){
    char *line = malloc(12 * sizeof(char));
    char *savefile_path = malloc(sizeof(SAVE_DIR) + sizeof(filename)+1);
    strcpy(savefile_path, SAVE_DIR);
    strcat(savefile_path, filename);
    FILE *save = fopen(savefile_path, "r");
    if(save){
        fscanf(save ,"Difficulty=%d\nGamemode=%d\nArtillery=%hu Bomb=%hu Tactical=%hu Simple=%hu\n", difficulty, gamemode, &(inventory->artillery), &(inventory->bomb), &(inventory->tactical), &(inventory->simple_missile));
        initialize_fleet(fleet);
        for(int i = 0; i < 5; i++){
            fscanf(save, "B=%hu,%hu,%d\n", &(fleet[i].position[0]), &(fleet[i].position[1]), &(fleet[i].orientation));
        }
        for(int i = 0; i < 10; i++){
            fgets(line, 12 * sizeof(char), save);
            strcpy(grid->grid[i], line);
        }
        if(*gamemode == ACTIVE){
            initialize_grid(grid_displayed_active, grid->height, grid->width);
            for (int i = 0; i < 10; i++) {
                fgets(line, 12 * sizeof(char), save);
                strcpy(grid_displayed_active->grid[i], line);
            }
        }
    }else{
        printf("No save file found, a new game will start.\n");
        new_game(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
    }
    free(savefile_path);
    free(line);
    fclose(save);
}

/**
 *
 * @param grid
 * @param grid_displayed_active
 * @param height
 * @param width
 * @param inventory
 * @param difficulty
 * @param gamemode
 * @param fleet
 */
void initialization(Grid *grid, Grid *grid_displayed_active, short int height, short int width, Inventory *inventory, Difficulty *difficulty, Mode *gamemode, Boat *fleet){
    int choice = 0;
    mkdir(SAVE_DIR);
    initialize_grid(grid, height, width);
    printf("Welcome to Naval Battle : enhanced edition\n");
    printf("Do you want to :\n  1 : Start a new game\n  2 : Resume the previous game\n  3 : Exit game\n");
    input_choice(&choice, 1, 3);
    switch(choice){
        case 1:
            new_game(grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
            break;
        case 2:
            load("save.txt", grid, grid_displayed_active, inventory, difficulty, gamemode, fleet);
            break;
        default:
            exit(0);
    }
}