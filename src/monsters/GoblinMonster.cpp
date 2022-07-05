#include "GoblinMonster.h"

#include <string>
#include <vector>

using namespace std;

GoblinMonster::GoblinMonster(std::string name, int attack, int defense, int exp, int money, int max_hp, int max_mp)
    : BaseMonster{name, attack, defense, exp, money, max_hp, max_mp}{
}

string GoblinMonster::serialize() {
    string result = "";
    result += (name + "$");
    result += (to_string(getHP()) + "$");
    result += (to_string(getMP()) + "$");

    return result;
}

BaseMonster* GoblinMonster::unserialize(string str) {
    vector<string> svec;
    int i = 0;
    int j = 0;
    while (j < str.length()) {
        if (str[j] == '$') {
            svec.push_back(str.substr(i, j - i));  // pos and len of string
            i = j + 1;
        }
        j++;
    }

    BaseMonster* ptr = new GoblinMonster(svec[0]);
    ptr->setHP(stoi(svec[1]));
    ptr->setMP(stoi(svec[2]));
    return ptr;
}
