#include "SkeletonMonster.h"

#include <string>
#include <vector>

#include "../misc/StringProcessor.h"

using namespace std;

SkeletonMonster::SkeletonMonster(std::string name, int attack, int defense, int exp, int money, int max_hp, int max_mp)
    : BaseMonster{name, attack, defense, exp, money, max_hp, max_mp} {}

string SkeletonMonster::serialize() {
    string result{};
    result += (name + "$");
    result += (to_string(getHP()) + "$");
    result += (to_string(getMP()) + "$");

    return result;
}

BaseMonster* SkeletonMonster::unserialize(string str) {
    vector<string> svec = StringProcessor::split(str, '$');

    BaseMonster* ptr = new SkeletonMonster(svec[0]);
    ptr->setHP(stoi(svec[1]));
    ptr->setMP(stoi(svec[2]));
    return ptr;
}
