#include "BattleMenu.h"

#include <conio.h>

#include <iostream>

#include "..\monsters\BaseMonster.h"
#include "..\players\NovicePlayer.h"
using namespace std;

BattleMenu::BattleMenu() {
    name = "Battle Menu";
    chosenIndex = 0;
    targets = vector<string>(1, "None");
    targetMenu = Menu("Targets", targets);  

    options = {
        "Normal attack",
        "Special skill",
        "Item",
        "Cancel"};
}

// if returns false, then go back to choosing target
bool BattleMenu::doAction(NovicePlayer* playerPtr, BaseMonster* monsterPtr, BackpackMenu& bpMenu) {
    switch (chosenIndex) {
        case 0: {  // normal attack
            int atk = playerPtr->getAttack();
            int def = monsterPtr->defense;
            int lost_hp = atk > def ? atk - def : 5;
            monsterPtr->setHP(monsterPtr->getHP() - lost_hp);
            cout << playerPtr->getName() << " attacked " << monsterPtr->name
                 << " and dealt " << lost_hp << " damage\n";
            return true;
        }
        case 1:
            if (playerPtr->specialSkill()) {  // if it works
                cout << playerPtr->getName() << " used special skill\n";
                return true;
            } else
                return false;
        case 2:
            bpMenu.chooseUser();
            bpMenu.chooseOption();
            if (bpMenu.doAction()) {
                return false;
            } else {
                getch();
                return false;
            }
        case 3:
            return false;  // cancel
        default:
            cout << "Invalid action\n";
            return false;
    }
    return false;
}

void BattleMenu::setTarget(int index, string name) {
    if (index < 0) {
        cout << "Out of index of targets(BattleMenu)\n";
        return;
    } else {
        if (targets.size() <= index)
            targets.resize(index + 1);
        targets[index] = name;
    }
    targetMenu = Menu("Targets", targets);
}

void BattleMenu::chooseTarget() {
    targetMenu.chooseOption();
    targetIndex = targetMenu.getChosenIndex();
}

int BattleMenu::getTargetIndex() const {
    return targetIndex;
}

string BattleMenu::getTargetName(int index) const {
    if (index < 0 || index >= targets.size()) {
        cout << "Out of index of targets(BattleMenu)\n";
        return "Invalid";
    }
    return targets[index];
}
