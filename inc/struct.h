#ifndef NAVAL_BATTLE_STRUCT_H
#define NAVAL_BATTLE_STRUCT_H

#define H 0
#define V 1

#define EASY 0
#define MEDIUM 1
#define HARD 2

typedef struct{
    unsigned short height;
    unsigned short width;
    char **boat_array;
}Grid;

typedef struct{
    unsigned short artillery;
    unsigned short tactical;
    unsigned short bomb;
    unsigned short simple_missile;
}Inventory;

typedef struct {
    unsigned short position[2];
    unsigned short size;
    unsigned short orientation;
}Boat;


#endif //NAVAL_BATTLE_STRUCT_H
