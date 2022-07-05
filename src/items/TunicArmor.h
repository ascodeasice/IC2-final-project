#include "ArmorItem.h"
#ifndef TUNICARMOR
#define TUNICARMOR
class TunicArmor : public ArmorItem {
   public:
   TunicArmor();
    TunicArmor(string, string, string, int, int, int);
};

#endif