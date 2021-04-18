#include "weapon.h"

int remaining_weapon(Inventory inventory){
    return inventory.artillery + inventory.bomb + inventory.tactical + inventory.simple_missile;
}