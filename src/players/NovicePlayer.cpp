#include "NovicePlayer.h"

#include <conio.h>
#include <stdlib.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../misc/StringProcessor.h"
#include "..\items.\ArmorItem.h"
#include "..\items.\ConsumableItem.h"
#include "..\items.\Item.h"
#include "..\items.\WeaponItem.h"
using namespace std;

vector<Item*> NovicePlayer::backpack = vector<Item*>(10, nullptr);
int NovicePlayer::money = 0;
int NovicePlayer::backpack_weight = 0;         // current weight of player’s backpack
int NovicePlayer::backpack_weight_limit = 12;  // limit on weight of backpack(10+level*2)
int NovicePlayer::backpack_slot_limit = 10;

NovicePlayer::NovicePlayer() : name{"anonymous"} {
    setLevel(1);
    setMoney(0);
    backpack = vector<Item*>(10, nullptr);
    updateBackpackWeight();
    weapon = nullptr;
    armor = nullptr;
}

NovicePlayer::NovicePlayer(int level) : name{"anonymous"} {
    setLevel(level);
    setMoney(0);
    backpack = vector<Item*>(backpack_slot_limit, nullptr);
    updateBackpackWeight();
    weapon = nullptr;
    armor = nullptr;
}

NovicePlayer::NovicePlayer(int level, string name) : name{name} {
    setLevel(level);
    setMoney(0);
    backpack = vector<Item*>(backpack_slot_limit, nullptr);
    updateBackpackWeight();
    weapon = nullptr;
    armor = nullptr;
}

NovicePlayer::NovicePlayer(const NovicePlayer& other) {
    name = other.name;
    hp = other.hp;
    mp = other.mp;
    exp = other.exp;
    money = other.money;
    level = other.level;
    attack = other.attack;
    defense = other.defense;
    max_hp = other.max_hp;
    max_mp = other.max_mp;
    lvup_exp = other.lvup_exp;
    backpack_weight_limit = other.backpack_weight_limit;
    backpack_slot_limit = other.backpack_slot_limit;
    backpack = vector<Item*>(backpack_slot_limit, new Item);
    for (int i = 0; i < backpack_slot_limit; i++) {
        backpack[i] = other.backpack[i];
    }
    updateBackpackWeight();
    weapon = new WeaponItem;
    weapon = other.weapon;
    armor = new ArmorItem;
    armor = other.armor;
}

void NovicePlayer::setName(string name) {
    this->name = name;
}

string NovicePlayer::getName() const {
    return name;
}

int levelUpExpFormula(int level) {
    // how much experience it takes to be level+1
    if (level <= 0)
        return 0;
    return ceil(pow(10, log2(level + 1)));
}

void NovicePlayer::setLevel(int level) {
    if (level <= 0) {
        cout << "Invalid level value\n";
        return;
    }
    this->level = level;
    max_hp = 100 + 10 * level;
    max_mp = 40 + 5 * level;
    attack = 20 + 5 * level;
    defense = 20 + 5 * level;

    setBackpack_weight_limit(10 + level * 2);

    setHp(max_hp);
    setMp(max_mp);
    lvup_exp = levelUpExpFormula(level);
}

int NovicePlayer::getLevel() const {
    return level;
}

void NovicePlayer::setHp(int val) {
    if (val < 0)
        hp = 0;
    else if (val > max_hp)
        hp = max_hp;
    else
        hp = val;
}

int NovicePlayer::getHp() const {
    return hp;
}

void NovicePlayer::setMp(int val) {  // NOTE check validation
    if (val < 0)
        mp = 0;
    else if (val > max_mp)
        mp = max_mp;
    else
        mp = val;
}

int NovicePlayer::getMp() const {
    return mp;
}

void NovicePlayer::setExp(int exp) {
    if (exp < 0) {
        cout << "Invalid experience value\n";
        return;
    }
    this->exp = exp;
    while (exp > lvup_exp) {
        lvup_exp = levelUpExpFormula(level);
        cout << "Level up! " << name << " is now level " << level << '\n';
        setLevel(level + 1);
    }
}

int NovicePlayer::getExp() const {
    return exp;
}

int NovicePlayer::getAttack() const {
    return attack;
}

void NovicePlayer::setAttack(int val) {
    if (val < 0) {
        cout << "can't set attack to negative values\n";
        return;
    }
    attack = val;
}

void NovicePlayer::setDefense(int val) {
    if (val < 0) {
        cout << "can't set defense to negative values\n";
        return;
    }
    defense = val;
}

int NovicePlayer::getDefense() const {
    return defense;
}

int NovicePlayer::getMaxHp() const {
    return max_hp;
}

int NovicePlayer::getMaxMp() const {
    return max_mp;
}

int NovicePlayer::getLvupExp() const {
    return lvup_exp;
}

bool NovicePlayer::specialSkill() {
    cout << "Novice Player doesn't have any skill\n";
    getch();
    return false;
}

string NovicePlayer::serialize() {
    string result = "";
    result += ("N$");
    result += (name + "$");
    result += (to_string(exp) + "$");
    result += (to_string(hp) + "$");
    result += (to_string(mp) + "$");

    return result;
}

NovicePlayer* NovicePlayer::unserialize(string str) {
    vector<string> svec = StringProcessor::split(str);
    int i = 0;
    int j = 0;
    NovicePlayer* ptr = new NovicePlayer();

    ptr->setName(svec[1]);
    ptr->setExp(stoi(svec[2]));
    ptr->setHp(stoi(svec[3]));
    ptr->setMp(stoi(svec[4]));
    return ptr;
}

void NovicePlayer::setMoney(int val) {
    if (val < 0) {
        cout << "Can't set negative money.";
        return;
    } else
        money = val;
}

int NovicePlayer::getMoney() const {
    return money;
}

void NovicePlayer::setBackpackWeight(int val) {
    if (val > 0)
        backpack_weight = val;
    else {
        cout << "Can't set weight to negative number\n";
    }
}

void NovicePlayer::setBackpack_weight_limit(int val) {
    if (val > 0)
        backpack_weight_limit = val;
    else {
        cout << "Can't set weight limit to negative number\n";
    }
}

void NovicePlayer::setBackpack_slot_limit(int val) {
    if (val < backpack_slot_limit) {
        cout << "can't set smaller backpack slot limit\n";
    } else if (val < 0) {
        cout << "Can't set slot limit to negative number\n";
    } else {
        backpack_slot_limit = val;
        backpack.resize(val, nullptr);
    }
}

bool NovicePlayer::putItem(Item* item) {
    if (item == nullptr)
        return false;
    if (backpack_weight + item->weight > backpack_weight_limit) {
        cout << "Can't pick up " << item->name << ", it's over weighted\n";
        return false;
    } else if (getOccupiedSlot() >= backpack_slot_limit) {
        cout << "The backpack is full.\n";
        return false;
    } else {
        // copy the item to be put into backpack, then put it in
        for (int i = 0; i < backpack_slot_limit; i++) {
            if (backpack[i] == nullptr) {
                backpack[i] = new Item;
                backpack[i] = item;
                cout << "You picked up " << item->name << '\n';
                updateBackpackWeight();
                return true;
            }
        }
        cout << "You can't put item into backpack for some reason.\n";
        return false;
    }
}

// NOTE these two functions should be called as "equip...(takeItem(i))""
bool NovicePlayer::equipArmor(ArmorItem* item) {
    if (item == nullptr) {
        cout << "Invalid item\n";
        return false;
    }

    int new_weight = backpack_weight + (armor == nullptr ? 0 : armor->weight) - item->weight;
    if (new_weight > backpack_weight_limit) {
        cout << "Can't put on " << item->name << ", the backpack would be overweighted\n";
        putItem(item);
        return false;
    }
    if (level < (item->level_required)) {
        cout << "Can't put on " << item->name << ", you don't have enough level(" << item->level_required << ")\n";
        putItem(item);
        return false;
    }
    if (armor == nullptr) {  // no item equipped
        armor = item;
        setDefense(defense + item->def_inc);
        cout << item->name << " is equipped\n";
        updateBackpackWeight();
        return true;
    } else {
        if (putItem(dynamic_cast<Item*>(armor))) {
            setDefense(defense - armor->def_inc + item->def_inc);
            armor = item;
            cout << item->name << " is equipped\n";
        } else {
            cout << "Can't put " << armor->name << " into backpack\n";
        }
        updateBackpackWeight();
        return true;
    }
}

bool NovicePlayer::equipWeapon(WeaponItem* item) {
    if (item == nullptr) {
        cout << "Invalid item\n";
        return false;
    }
    int new_weight = backpack_weight + (weapon == nullptr ? 0 : weapon->weight) - item->weight;
    if (new_weight > backpack_weight_limit) {
        cout << "Can't put on " << item->name << ", the backpack would be overweighted\n";
        putItem(item);
        return false;
    } else if (level < (item->level_required)) {
        cout << "Can't put on " << item->name << ", you don't have enough level(" << item->level_required << ")\n";
        putItem(item);
        return false;
    } else if (weapon == nullptr) {  // not equipping
        weapon = item;
        setAttack(attack + weapon->atk_inc);
        cout << weapon->name << " is equipped\n";
        return true;
    } else {
        if (putItem(dynamic_cast<Item*>(weapon))) {  // TODO check if this work
            setAttack(attack - weapon->atk_inc + item->atk_inc);
            weapon = item;
            cout << item->name << " is equipped\n";
        } else {
            cout << "Can't put " << weapon->name << " into backpack\n";
        }
        return true;
    }
}

void NovicePlayer::displayBackpack() {
    cout << "Weapon:" << (weapon == nullptr ? "None" : weapon->name) << '\n'
         << "Armor:" << (armor == nullptr ? "None" : armor->name) << '\n';
    cout << "BackPack:\n";
    cout << "Weight Limit:" << backpack_weight_limit << ", current weight:" << backpack_weight << '\n';
    for (int i = 0; i < backpack_slot_limit; i++) {
        cout << i + 1 << ". " << left << setw(15) << (backpack[i] == nullptr ? "None" : backpack[i]->name);
        if (backpack[i] != nullptr)
            cout << "Effects: " << setw(10) << backpack[i]->effects << "Level required:" << backpack[i]->level_required << '\n';
        else
            cout << "\n";
    }
    cout << "Enter the index of item(1~" << backpack_slot_limit << "), or input -1 to quit backpack:\n";
}

// It also remove them from the backpack, so put them back if not using it
Item* NovicePlayer::takeItem(int i) {
    // NOTE 0-indexed
    if (i < 0 || i >= backpack_slot_limit) {
        cout << "Invalid index of backpack, can't drop item\n";
        return nullptr;
    } else {
        Item* item = backpack[i];
        backpack[i] = nullptr;
        updateBackpackWeight();
        return item;
    }
}

int NovicePlayer::getOccupiedSlot() {
    int occupied_slot = 0;
    for (int i = 0; i < backpack_slot_limit; i++) {
        if (backpack[i] != nullptr)
            occupied_slot++;
    }
    return occupied_slot;
}

bool NovicePlayer::useConsumable(ConsumableItem* item) {
    if (item == nullptr) {
        cout << "Invalid item\n";
        return false;
    }

    if (level < item->level_required) {
        cout << "Not enough level to use " << item->name << "\n";
        return false;
    }
    cout << "you used " << item->name << "\n";
    setHp(hp + (item->hp_inc));
    setMp(mp + (item->mp_inc));
    cout << "You now have: " << hp << "HP and " << mp << " MP\n";
    delete item;
    return true;
}

int NovicePlayer::getBackpackSlotLimit() const {
    return backpack_slot_limit;
}

void NovicePlayer::updateBackpackWeight() {
    int totalWeight = 0;
    for (int i = 0; i < backpack_slot_limit; i++) {
        if (backpack[i] == nullptr)
            continue;
        totalWeight += backpack[i]->weight;
    }
    backpack_weight = totalWeight;
}

ArmorItem* NovicePlayer::getArmor() const {
    return armor;
}

WeaponItem* NovicePlayer::getWeapon() const {
    return weapon;
}