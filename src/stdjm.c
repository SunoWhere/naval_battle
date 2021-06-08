#include "stdjm.h"

/**
 *
 * @param choice
 * @param inf
 * @param sup
 */
void input_choice(int *choice, int inf, int sup){
    char input[3];
    fgets(input, 3, stdin);
    while(!(*choice = atoi(input)) || (*choice < inf || *choice > sup)){
        printf("Please enter a valid choice : \n");
        fgets(input, 3, stdin);
    }
}