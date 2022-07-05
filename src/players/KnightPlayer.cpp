#include "KnightPlayer.h"

#include <conio.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

KnightPlayer::KnightPlayer() {
    setName("anonymous");
    setLevel(1);
}

KnightPlayer::KnightPlayer(int level) {
    setName("anonymous");
    setLevel(level);
}

KnightPlayer::KnightPlayer(int level, string name) {
    setName(name);
    setLevel(level);
}

KnightPlayer::KnightPlayer(const KnightPlayer& other) : NovicePlayer(other.getLevel(), other.getName()) {
    setName(other.getName());
    setLevel(other.getLevel());
}

void KnightPlayer::setLevel(int level) {
    if (level <= 0) {
        cout << "Invaild level value\n";
        return;
    }
    this->level = level;
    max_hp = 150 + 25 * level;
    max_mp = 70 + 10 * level;
    attack = 40 + 10 * level;
    defense = 20 + 12 * level;

    setBackpack_weight_limit(10 + level * 2);

    setHp(max_hp);
    setMp(max_mp);
    lvup_exp = level <= 0 ? 0 : ceil(pow(10, log2(level + 1)));
    setExp(lvup_exp = level <= 0 ? 0 : ceil(pow(10, log2(level - 1))));
}

bool KnightPlayer::specialSkill() {
    // heal
    if (getMp() > level * 5) {
        setMp(getMp() - level * 5);
        setHp(getHp() + level * 10);
        cout << getName() << " now has " << getHp() << " HP\n";
        getch();

        return true;
    } else {
        cout << "Not enough MP.\n";
        getch();
        return false;
    }
}

string KnightPlayer::serialize() {
    string result = "";
    result += ("K$");
    result += (getName() + "$");
    result += (to_string(getExp()) + "$");
    result += (to_string(getHp()) + "$");
    result += (to_string(getMp()) + "$");

    return result;
}

NovicePlayer* KnightPlayer::unserialize(string str) {
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
    NovicePlayer* ptr = new KnightPlayer();

    ptr->setName(svec[1]);
    ptr->setExp(stoi(svec[2]));
    ptr->setHp(stoi(svec[3]));
    ptr->setMp(stoi(svec[4]));
    return ptr;
}
