#include "ShieldArmor.h"

ShieldArmor::ShieldArmor():ArmorItem("shield", "An ordinary shield", " +15 def", 3, 3, 15) {

}

ShieldArmor::ShieldArmor(string name = "shield", string des = "An ordinary shield", string effects = " +15 def", int level_required = 3, int weight = 3, int def_inc = 15) : ArmorItem(name, des, effects, level_required, weight, def_inc) {
}
