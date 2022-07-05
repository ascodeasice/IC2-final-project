#include "ArmorItem.h"
#ifndef SHIELDARMOR
#define SHIELDARMOR
class ShieldArmor : public ArmorItem {
   public:
   ShieldArmor();
    ShieldArmor(string, string, string, int, int, int);
};

#endif