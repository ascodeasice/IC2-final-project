#include "LifePotion.h"

LifePotion::LifePotion():ConsumableItem("life potion", "a bottle of red potion.", "+20 hp", 0, 1, 20, 0) {
}
LifePotion::LifePotion(string name = "life potion", string des = "a bottle of red potion.", string effects = "+20 hp", int level_required = 0, int weight = 1, int hp_inc = 20, int mp_inc = 0) : ConsumableItem(name, des, effects, level_required, weight, hp_inc, mp_inc) {
}
