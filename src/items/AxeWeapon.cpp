#include "AxeWeapon.h"

Axe::Axe() :WeaponItem("Iron Axe", "An ordinary iron Axe", "+15atk", 2, 3, 15) {
}

Axe::Axe(string name = "Iron Axe", string des = "An ordinary iron Axe", string effects = " +15atk", int level_required = 2, int weight = 3, int atk_inc = 15) : WeaponItem(name, des, effects, level_required, weight, atk_inc) {
}
