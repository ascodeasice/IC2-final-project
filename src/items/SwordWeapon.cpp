#include "SwordWeapon.h"

Sword::Sword() : WeaponItem("Iron Sword", "An ordinary iron sword", "+10 atk", 2, 2, 10) {
}

Sword::Sword(string name = "Iron Sword", string des = "An ordinary iron sword", string effects = " +10atk", int level_required = 2, int weight = 2, int atk_inc = 10) : WeaponItem(name, des, effects, level_required, weight, atk_inc) {
}