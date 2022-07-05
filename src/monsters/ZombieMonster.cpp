#include "ZombieMonster.h"

#include <string>
#include <vector>

#include "../misc/StringProcessor.h"

using namespace std;

ZombieMonster::ZombieMonster(std::string name, int attack, int defense, int exp, int money, int max_hp, int max_mp)
    : BaseMonster{name, attack, defense, exp, money, max_hp, max_mp} {}

string ZombieMonster::serialize() {
    string result{};
    result += (name + "$");
    result += (to_string(getHP()) + "$");
    result += (to_string(getMP()) + "$");

    return result;
}

BaseMonster* ZombieMonster::unserialize(string str) {
    vector<string> svec = StringProcessor::split(str, '$');

    BaseMonster* ptr = new ZombieMonster(svec[0]);
    ptr->setHP(stoi(svec[1]));
    ptr->setMP(stoi(svec[2]));
    return ptr;
}
