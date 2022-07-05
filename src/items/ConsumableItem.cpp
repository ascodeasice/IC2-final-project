#include "ConsumableItem.h"

#include <string>
#include <vector>
using namespace std;

#include "..\players.\NovicePlayer.h"

ConsumableItem::ConsumableItem(string name = "water", string des = "No description", string effects = "No effects", int level_required = 0, int weight = 0, int hp_inc = 0, int mp_inc = 0) : Item(name, des, effects, level_required, weight, 'c'), hp_inc{hp_inc}, mp_inc{mp_inc} {
}

string ConsumableItem::serialize() {
    string result = "";
    string newName = name;
    string newDes = description;
    string newEffect = effects;
    // replace all space in description into _
    while (newName.find(" ") != string::npos) {
        newName.replace(newName.find(" "), 1, "_");
    }
    while (newDes.find(" ") != string::npos) {
        newDes.replace(newDes.find(" "), 1, "_");
    }
    while (newEffect.find(" ") != string::npos) {
        newEffect.replace(newEffect.find(" "), 1, "_");
    }

    result += ("C$");
    result += (newName + "$");
    result += (newDes + "$");
    result += (newEffect + "$");
    result += (to_string(level_required) + "$");
    result += (to_string(weight) + "$");
    result += (to_string(hp_inc) + "$");
    result += (to_string(mp_inc) + "$");

    return result;
}

Item* ConsumableItem::unserialize(string str) {
    if (str == "None" || str == "")
        return nullptr;

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

    // replace _ into space
    for (int i = 1; i <= 3; i++) {
        while (svec[i].find('_') != string::npos) {
            svec[i].replace(svec[i].find("_"), 1, " ");
        }
    }
    Item* ptr = new ConsumableItem(svec[1], svec[2], svec[3], stoi(svec[4]), stoi(svec[5]), stoi(svec[6]), stoi(svec[7]));
    return ptr;
}
