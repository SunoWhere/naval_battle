#include "stdjm.h"

/**
 * Cette fonction permet la récupération du choix du joueur, cette fonction est uniquement destinée aux entrées
 * numériques comprises entre les bornes définiés lors de l'appel de la fonction
 * @param choice - Pointeur permettant de récupérer le choix du joueur
 * @param inf - Borne inférieur
 * @param sup - Borne supérieur
 */
void input_choice(int *choice, int inf, int sup){
    char input[3];
    fgets(input, 3, stdin);
    while(!(*choice = atoi(input)) || (*choice < inf || *choice > sup)){
        printf("Please enter a valid choice : \n");
        fgets(input, 3, stdin);
    }
}