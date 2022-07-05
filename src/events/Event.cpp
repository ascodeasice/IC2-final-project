#include "Event.h"

#include <conio.h>

#include <string>

#include "../items/ArmorItem.h"
#include "../items/ConsumableItem.h"
#include "../items/WeaponItem.h"
#include "../menu/BackpackMenu.h"
#include "../misc/Battle.h"
#include "../misc/Field.h"
#include "../misc/StringProcessor.h"
#include "../monsters/GoblinMonster.h"
#include "../monsters/JWMonster.h"
#include "../monsters/SkeletonMonster.h"
#include "../monsters/ZombieMonster.h"

using namespace std;

Event::Event(int num, string name, string dialogue, int exp_inc, string itemStr, char type, string monsterStr)
    : name{name}, dialogue{dialogue}, num{num}, exp_inc{exp_inc}, type{type} {
    switch (itemStr[0]) {
        case 'A':
            item = ArmorItem::unserialize(itemStr);
            break;
        case 'W':
            item = WeaponItem::unserialize(itemStr);
            break;
        case 'C':
            item = ConsumableItem::unserialize(itemStr);
            break;
        default:
            item = nullptr;
            break;
    }
    if (monsterStr == "None")
        monsterList = {};
    else {
        vector<string> monsterSvec = StringProcessor::split(monsterStr, '+');
        for (auto& s : monsterSvec) {
            switch (s[0]) {
                case 'G':
                    monsterList.push_back(new GoblinMonster);
                    break;
                case 'J':
                    monsterList.push_back(new JWMonster);
                    break;
                case 'Z':
                    monsterList.push_back(new ZombieMonster);
                    break;
                case 'S':
                    monsterList.push_back(new SkeletonMonster);
                    break;
                default:
                    cout << "Unknown monster(Event.cpp)\n";
            }
        }
    }
}

bool Event::begin(vector<NovicePlayer*> playerList, BackpackMenu& bpMenu) {
    startDialogue();
    startBattle(playerList, bpMenu);
    return (reward(playerList));
}

void Event::startDialogue() {
    vector<string> sentences = StringProcessor::split(dialogue, '^');
    for (auto& s : sentences) {
        system("cls");
        cout << s << '\n';
        getch();
    }
}

bool Event::reward(vector<NovicePlayer*> playerList) {
    if (playerList.size() == 0) {
        cout << "Can't pass empty playerList!(Event.cpp)\n";
        return false;
    }
    if (exp_inc != 0) {
        cout << "You get " << exp_inc << " exp\n";
        getch();
    }
    for (auto player : playerList)
        player->setExp(player->getExp() + exp_inc);

    if (item == nullptr)  // no item
        return true;
    else {
        bool valid = (playerList[0]->putItem(item));
        getch();
        return valid;
    }
}

void Event::startBattle(vector<NovicePlayer*> playerList, BackpackMenu& bpMenu) {
    if (monsterList.size() == 0)
        return;
    Battle battle{int(playerList.size()), int(monsterList.size())};
    for (int i = 0; i < playerList.size(); i++) {
        battle.setPlayer(i, playerList[i]);
    }
    for (int i = playerList.size(); i < playerList.size() + monsterList.size(); i++) {
        battle.setMonster(i, monsterList[i - playerList.size()]);
    }
    battle.begin(bpMenu);
}