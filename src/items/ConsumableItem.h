// #include "..\players.\NovicePlayer.h"
#include <string>

#include "Item.h"

#ifndef CONSUMABLEITEM
#define CONSUMABLEITEM
class ConsumableItem : public Item {
   public:
    ConsumableItem(string, string, string, int, int, int, int);  // don't need type parameter(is 'm')
    std::string serialize();
    static Item* unserialize(std::string);

    int hp_inc;
    int mp_inc;
};

#endif
