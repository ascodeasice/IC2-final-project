#include "MagicPotion.h"

MagicPotion::MagicPotion() : ConsumableItem("Magic potion", "a bottle of blue potion.", "+20 mp", 0, 1, 0, 20) {}

MagicPotion::MagicPotion(string name = "Magic potion", string des = "a bottle of blue potion.", string effects = "+20 mp", int level_required = 0, int weight = 1, int hp_inc = 0, int mp_inc = 20) : ConsumableItem(name, des, effects, level_required, weight, hp_inc, mp_inc) {
}
