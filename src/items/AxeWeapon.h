#include "WeaponItem.h"
#ifndef AXEWEAPON
#define AXEWEAPON
class Axe : public WeaponItem {
   public:
    Axe();
    Axe(string, string, string, int, int, int);
};

#endif