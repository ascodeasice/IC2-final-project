#include "BackpackMenu.h"

#include <conio.h>
#include <stdlib.h>

#include <iomanip>
#include <iostream>
#include <vector>

#include "../players/NovicePlayer.h"

using namespace std;

void BackpackMenu::setOptions() {
    auto bp = NovicePlayer::backpack;
    options.resize(bp.size() + 1);
    for (int i = 0; i < bp.size(); i++) {
        if (bp[i] == nullptr)
            options[i] = "None";
        else
            options[i] = bp[i]->name;
    }
    options[bp.size()] = "Cancel";
}

BackpackMenu::BackpackMenu() {
    ;  // do nothing
}

BackpackMenu::BackpackMenu(vector<NovicePlayer*>& pList) {
    name = "Backpack";
    chosenIndex = 0;
    playerIndex = 0;
    action = 'U';

    playerList.resize(pList.size());
    for (int i = 0; i < pList.size(); i++) {
        playerList[i] = pList[i];
    }

    setOptions();
}

void BackpackMenu::setPlayer(int index, NovicePlayer* playerPtr) {
    if (index < 0) {
        cout << "Can't set negative index(BackpackMenu)\n";
        return;
    }
    playerList[index] = playerPtr;
}

// choose user of the item, then change playerIndex into the chosen one
void BackpackMenu::chooseUser() {
    vector<string> nameList;
    for (auto& player : playerList) {
        nameList.push_back(player->getName());
    }
    cout << nameList.size() << '\n';
    Menu playerMenu("players", nameList);
    playerMenu.chooseOption();
    playerIndex = playerMenu.getChosenIndex();
}

void BackpackMenu::display() {
    setOptions();
    system("cls");  // clear the screen
    cout << name << '\n'
         << "Weight:" << setw(3) << NovicePlayer::backpack_weight << "/" << setw(3) << NovicePlayer::backpack_weight_limit << '\n';
    std::cout << std::string(50, '=') << std::endl;

    NovicePlayer* user = playerList[playerIndex];
    cout << user->getName() << ":\n";
    cout << "HP:" << setw(3) << user->getHp() << "/" << setw(3) << user->getMaxHp() << '\t';
    cout << "MP:" << setw(3) << user->getMp() << "/" << setw(3) << user->getMaxMp() << '\t';
    cout << "Level:" << user->getLevel() << '\n';
    cout << "Attack:" << user->getAttack() << '\t' << "Defense:" << user->getDefense() << '\t' << "Money:" << NovicePlayer::money << '\n';

    cout << "Weapon:";
    if (user->getWeapon() != nullptr)
        cout << user->getWeapon()->name << ", " << user->getWeapon()->effects << '\n';
    else
        cout << "None\n";

    cout << "Armor:";
    if (user->getArmor() != nullptr)
        cout << user->getArmor()->name << ", " << user->getArmor()->effects << '\n';
    else
        cout << "None\n";

    std::cout << std::string(50, '=') << std::endl;

    for (int i = 0; i < options.size(); i++) {
        if (i == chosenIndex)
            cout << "*";
        cout << options[i] << '\n';
    }
    cout << std::string(50, '=') << endl;

    if (options[chosenIndex] != "Cancel" && options[chosenIndex] != "None") {
        NovicePlayer::backpack[chosenIndex]->display();
        cout << std::string(50, '=') << endl;
    }

    cout << "Press W,S to choosen item, A to use/equip, D to discard\n";
}

void BackpackMenu::chooseOption() {
    char input{};

    while (!chosen) {
        display();
        input = getch();
        switch (toupper(input)) {
            case 'S':
                setChosenIndex(chosenIndex + 1);
                break;
            case 'W':
                setChosenIndex(chosenIndex - 1);
                break;
            case 'A':  // use
                action = 'U';
                chosen = true;
                break;
            case 'D':  // discard
                action = 'D';
                chosen = true;
                break;
        }
    }

    chosen = false;  // reset the state
}

bool BackpackMenu::doAction() {  // D(discard) or U(use)
    setOptions();

    NovicePlayer* user = playerList[playerIndex];
    if (options[chosenIndex] == "Cancel")
        return true;
    else if (options[chosenIndex] == "None") {
        cout << "Can't choose non-existent item\n";
        return false;
    } else if (user == nullptr) {
        cout << "No user chosen\n";
        return false;
    } else {
        Item* item = NovicePlayer::backpack[chosenIndex];
        switch (action) {
            case 'D':  // discard
                if (user->takeItem(chosenIndex) != nullptr) {
                    cout << "Discarded " << item->name << '\n';
                    getch();
                    return true;
                }
                return false;
            case 'U':
                switch (item->type) {
                    case 'w':
                        (user->equipWeapon(static_cast<WeaponItem*>(user->takeItem(chosenIndex))));
                        return false;
                    case 'a':
                        (user->equipArmor(static_cast<ArmorItem*>(user->takeItem(chosenIndex))));
                        return false;
                    case 'c':
                        (user->useConsumable(static_cast<ConsumableItem*>(user->takeItem(chosenIndex))));
                        return false;
                    default:
                        cout << "Unknown item(BackpackMenu.cpp)\n";
                        return false;
                }
                break;
            default:
                cout << "Invalid action(BackpackMenu.cpp)\n";
                return false;
        }
    }
}