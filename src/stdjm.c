#include "stdjm.h"

int str_to_int(char *input){
    int number = 0;
    if(input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
    for(int i = 0; input[i] != '\0'; i++) {
        if(!isdigit(input[i])){
            return 0;
        }
    }
    for(int i = strlen(input) - 1, power = 1; i >= 0  ; i--, power *= 10) {
        number += (input[i]-48) * power;
    }
    return number;
}

void input_choice(int *choice, int inf, int sup){
    char input[5];
    do {
        fgets(input, 5, stdin);
        while(!(*choice = str_to_int(input))){
            printf("Please enter a valid choice : \n");
            fgets(input, 5, stdin);
        }
    }while(*choice < inf || *choice > sup);
}
