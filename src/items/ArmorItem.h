#include <string>

#include "Item.h"

#ifndef ARMORITEM
#define ARMORITEM
class ArmorItem : public Item {
   public:
    ArmorItem();
    ArmorItem(string, string, string, int, int, int);  // don't need type parameter(is 'a')
    std::string serialize();
    static Item* unserialize(std::string);
    int def_inc;  // number of increment of defense
};
#endif