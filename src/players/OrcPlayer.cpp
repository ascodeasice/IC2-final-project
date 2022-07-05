#include "OrcPlayer.h"

#include <conio.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../misc/StringProcessor.h"

using namespace std;

OrcPlayer::OrcPlayer() {
    setName("anonymous");
    setLevel(1);
}

OrcPlayer::OrcPlayer(int level) {
    setName("anonymous");
    setLevel(level);
}

OrcPlayer::OrcPlayer(int level, string name) {
    setName(name);
    setLevel(level);
}

OrcPlayer::OrcPlayer(const OrcPlayer& other) : NovicePlayer(other.getLevel(), other.getName()) {
    setName(other.getName());
    setLevel(level);
}

void OrcPlayer::setLevel(int level) {
    if (level <= 0) {
        cout << "Invaild level value\n";
        return;
    }
    this->level = level;
    max_hp = 200 + 20 * level;
    max_mp = 50 + 5 * level;
    attack = 50 + 12 * level;
    defense = 30 + 10 * level;

    setBackpack_weight_limit(10 + level * 2);

    setHp(max_hp);
    setMp(max_mp);
    lvup_exp = level <= 0 ? 0 : ceil(pow(10, log2(level + 1)));
    setExp(lvup_exp = level <= 0 ? 0 : ceil(pow(10, log2(level - 1))));
}

bool OrcPlayer::specialSkill() {
    cout << "The Orc is strong, he doesn't need special skill.\n";
    getch();
    return false;
}

string OrcPlayer::serialize() {
    string result = "";
    result += ("O$");
    result += (getName() + "$");
    result += (to_string(getExp()) + "$");
    result += (to_string(getHp()) + "$");
    result += (to_string(getMp()) + "$");

    return result;
}

NovicePlayer* OrcPlayer::unserialize(string str) {
    vector<string> svec = StringProcessor::split(str, '$');
    NovicePlayer* ptr = new OrcPlayer();

    ptr->setName(svec[1]);
    ptr->setExp(stoi(svec[2]));
    ptr->setHp(stoi(svec[3]));
    ptr->setMp(stoi(svec[4]));
    return ptr;
}
