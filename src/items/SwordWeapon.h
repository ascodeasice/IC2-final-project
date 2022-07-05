#include "WeaponItem.h"
#ifndef SWORDWEAPON
#define SWORDWEAPON
class Sword : public WeaponItem {
   public:
   Sword();
    Sword(string, string, string, int, int, int);
};

#endif