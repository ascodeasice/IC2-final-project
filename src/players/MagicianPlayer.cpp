#include "MagicianPlayer.h"

#include <conio.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

MagicianPlayer::MagicianPlayer() {
    setName("anonymous");
    setLevel(1);
}

MagicianPlayer::MagicianPlayer(int level) {
    setName("anonymous");
    setLevel(level);
}

MagicianPlayer::MagicianPlayer(int level, string name) {
    setName(name);
    setLevel(level);
}

MagicianPlayer::MagicianPlayer(const MagicianPlayer& other) : NovicePlayer(other.getLevel(), other.getName()) {
    setName(other.getName());
    setLevel(level);
}

void MagicianPlayer::setLevel(int level) {
    if (level <= 0) {
        cout << "Invaild level value\n";
        return;
    }
    this->level = level;
    max_hp = 120 + 15 * level;
    max_mp = 100 + 15 * level;
    attack = 30 + 8 * level;
    defense = 20 + 7 * level;

    setBackpack_weight_limit(10 + level * 2);

    setHp(max_hp);
    setMp(max_mp);
    lvup_exp = level <= 0 ? 0 : ceil(pow(10, log2(level + 1)));
    setExp(lvup_exp = level <= 0 ? 0 : ceil(pow(10, log2(level - 1))));
}

bool MagicianPlayer::specialSkill() {
    if (getMp() > level * 5) {
        setMp(getMp() - level * 5);
        setAttack(getAttack() + 3 * level);
        setDefense(getDefense() + 3 * level);
        cout << getName() << " now has " << attack << " atk, " << defense << " def\n";
        getch();
        return true;
    } else {
        cout << "Not enough MP.\n";
        getch();
        return false;
    }
}

string MagicianPlayer::serialize() {
    string result = "";
    result += ("M$");
    result += (getName() + "$");
    result += (to_string(getExp()) + "$");
    result += (to_string(getHp()) + "$");
    result += (to_string(getMp()) + "$");

    return result;
}

NovicePlayer* MagicianPlayer::unserialize(string str) {
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

    NovicePlayer* ptr = new MagicianPlayer();

    ptr->setName(svec[1]);
    ptr->setExp(stoi(svec[2]));
    ptr->setHp(stoi(svec[3]));
    ptr->setMp(stoi(svec[4]));
    return ptr;
}
