#include "BaseMonster.h"

using namespace std;

int BaseMonster::count = 0;

BaseMonster::BaseMonster(std::string name, int attack, int defense, int exp, int money, int max_hp, int max_mp)
    : name{name}, attack{attack}, defense{defense}, exp{exp}, money{money}, max_hp{max_hp}, max_mp{max_mp} {
    count++;
    hp = max_hp;
    mp = max_mp;
}

int BaseMonster::getInstanceCount() {
    return count;
}

BaseMonster::~BaseMonster() {
    count--;
}

void BaseMonster::setHP(int val) {
    if (val <= 0)
        hp = 0;
    else if (val > max_hp)
        hp = max_hp;
    else
        hp = val;
}
int BaseMonster::getHP() const {
    return hp;
}
void BaseMonster::setMP(int val) {
    if (val <= 0)
        mp = 0;
    else if (val > max_mp)
        mp = max_mp;
    else
        mp = val;
}
int BaseMonster::getMP() const {
    return mp;
}