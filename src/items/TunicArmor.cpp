#include "TunicArmor.h"

TunicArmor::TunicArmor() : ArmorItem("Tunic Armor", "An ordinary tunic armor", "+10 def", 2, 3, 10) {
}

TunicArmor::TunicArmor(string name = "Tunic Armor", string des = "An ordinary tunic armor", string effects = " +10 def", int level_required = 2, int weight = 3, int def_inc = 10) : ArmorItem(name, des, effects, level_required, weight, def_inc) {
}
