#ifndef NAVAL_BATTLE_STRUCT_H
#define NAVAL_BATTLE_STRUCT_H

#define SAVE_DIR "save/"

typedef enum{
    CLASSIC,
    BLIND,
    ACTIVE
}Mode;

typedef enum{
    EASY,
    MEDIUM,
    HARD
}Difficulty;

typedef enum{
    VERTICAL,
    HORIZONTAL
}Orientation;

typedef enum{
    ARTILLERY,
    BOMB,
    TACTICAL,
    SIMPLE,
    NONE
}Weapon;

typedef struct{
    unsigned short height;
    unsigned short width;
    char **grid;
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
    Orientation orientation;
}Boat;


#endif //NAVAL_BATTLE_STRUCT_H
