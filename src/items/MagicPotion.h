#include "ConsumableItem.h"

#ifndef MAGICPOTION
#define MAGICPOTION
class MagicPotion : public ConsumableItem {
   public:
    MagicPotion();
    MagicPotion(string, string, string, int, int, int, int);
};

#endif