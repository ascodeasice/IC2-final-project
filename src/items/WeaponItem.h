#include <string>

#include "Item.h"
#ifndef WEAPONITEM
#define WEAPONITEM
class WeaponItem : public Item {
   public:
    WeaponItem();
    WeaponItem(string, string, string, int, int, int);
    std::string serialize();
    static Item* unserialize(std::string);
    int atk_inc;  // the number of increment on attack after equipping this item
};
#endif