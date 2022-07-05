#include "ConsumableItem.h"

#ifndef LIFEPOTION
#define LIFEPOTION
class LifePotion : public ConsumableItem {
   public:
    LifePotion();
    LifePotion(string, string, string, int, int, int, int);
};

#endif