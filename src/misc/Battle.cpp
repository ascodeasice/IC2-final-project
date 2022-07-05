#include "Battle.h"

#include <conio.h>
#include <stdlib.h>

#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

#include "../menu/BackpackMenu.h"
#include "..\monsters\BaseMonster.h"
#include "..\players\NovicePlayer.h"
using namespace std;

Battle::Battle(int pNum, int mNum) {
    ActionList = new Character[pNum + mNum];
    playerNum = pNum;
    monsterNum = mNum;
    turn = 1;
    winner = '?';
}

Battle::~Battle() {
    delete[] ActionList;
}

void Battle::displayData(const BaseMonster& monster) const {
    cout << left << setw(15) << "Name:" << setw(4) << monster.name << '\n'
         << left << setw(15) << "HP:" << setw(4) << monster.getHP() << "/" << monster.max_hp << '\n'
         << left << setw(15) << "MP:" << setw(4) << monster.getMP() << "/" << monster.max_mp << '\n';
    cout << string(50, '=') << '\n';
}

void Battle::displayData(const NovicePlayer& player) const {
    cout << left << setw(15) << "Name:" << setw(4) << player.getName() << '\n'
         << left << setw(15) << "HP:" << setw(4) << player.getHp() << "/" << player.getMaxHp() << '\n'
         << left << setw(15) << "MP:" << setw(4) << player.getMp() << "/" << player.getMaxMp() << '\n';
    cout << string(50, '=') << '\n';
}

void Battle::setPlayer(int i, NovicePlayer* player) {
    if (i >= playerNum + monsterNum) {
        cout << "Out of index, can't set player\n";
        return;
    }
    ActionList[i] = Character{'p', true, player};
}

void Battle::setMonster(int i, BaseMonster* monster) {
    if (i >= playerNum + monsterNum) {
        cout << "Out of index, can't set monster\n";
        return;
    }

    ActionList[i] = Character{'m', true, monster};
}

char Battle::getWinner() const {
    return winner;
}

// team based: p1,p2,p3,m1,m2,m3
void Battle::determineOrder() {
    Character* order = new Character[playerNum + monsterNum];

    // done to prevent duplicated member

    // start with player team
    int i = 0;
    while (i < playerNum) {
        for (int j = 0; j < playerNum + monsterNum; j++) {
            if (ActionList[j].type == 'p') {
                order[i] = ActionList[j];
                i++;
            }
        }
    }

    // end with monster team
    i = playerNum;
    while (i < playerNum + monsterNum) {
        for (int j = 0; j < playerNum + monsterNum; j++) {
            if (ActionList[j].type == 'm') {
                order[i] = ActionList[j];
                i++;
            }
        }
    }

    ActionList = order;
}

// players then monsters
void Battle::begin(BackpackMenu& bpMenu) {
    bool all_monster_dead = false;
    bool all_player_dead = false;

    // set targets
    for (int i = playerNum; i < playerNum + monsterNum; i++) {
        menu.setTarget(i - playerNum, static_cast<BaseMonster*>(ActionList[i].instance)->name);
    }
    // SECTION battle logic
    while ((!all_player_dead) && (!all_monster_dead)) {
        for (int i = 0; i < playerNum + monsterNum; i++) {
            system("cls");
            cout << "\nTurn " << turn << ":\n";
            if (!ActionList[i].alive)
                continue;
            // alive player
            if (ActionList[i].type == 'p' && static_cast<NovicePlayer*>(ActionList[i].instance)->getHp() > 0) {
                NovicePlayer* tmp_player = static_cast<NovicePlayer*>(ActionList[i].instance);
                BaseMonster* attackedMonster = nullptr;

                cout << tmp_player->getName() << "'s turn\n";
                displayData(*tmp_player);
                getch();

                // SECTION choose target
                while (true) {
                    while (true) {
                        menu.chooseTarget();
                        int index = menu.getTargetIndex() + playerNum;  // from targets index to ActionList index
                        if (menu.getTargetName(menu.getTargetIndex()) == "dead") {
                            cout << "It's already dead, choose another target.\n";
                            getch();
                            continue;
                        } else if (index >= playerNum + monsterNum) {
                            cout << "Can't choose none existing target";
                            getch();
                            continue;
                        } else {
                            attackedMonster = static_cast<BaseMonster*>(ActionList[index].instance);
                            menu.chooseOption();
                            if (menu.doAction(tmp_player, attackedMonster, bpMenu)) {
                                break;
                            } else
                                continue;
                        }
                    }

                    // SECTION choose move

                    if (attackedMonster->getHP() <= 0) {
                        ActionList[menu.getTargetIndex() + playerNum].alive = false;
                        cout << attackedMonster->name << " is dead.\n";
                        menu.setTarget(menu.getTargetIndex(), "dead");
                        getch();
                    } else {
                        displayData(*attackedMonster);
                        getch();
                    }
                    break;  // end the player's turn
                }

                // check if every monster is dead
                all_monster_dead = true;
                for (int i = playerNum; i < playerNum + monsterNum; i++) {
                    if (ActionList[i].alive) {
                        all_monster_dead = false;
                        break;
                    }
                }
            } else if (ActionList[i].type == 'm') {
                system("cls");
                BaseMonster* tmp_monster = static_cast<BaseMonster*>(ActionList[i].instance);
                cout << tmp_monster->name << "'s turn\n";
                displayData(*tmp_monster);

                int targetIndex = rand() % playerNum;  // get random index until get an alive player
                while (static_cast<NovicePlayer*>(ActionList[targetIndex].instance)->getHp() < 0) {
                    targetIndex = rand() % playerNum;
                }

                NovicePlayer* attackedPlayer = static_cast<NovicePlayer*>(ActionList[targetIndex].instance);

                int atk = tmp_monster->attack;
                int def = attackedPlayer->getDefense();
                // if attack is less than defense, lose (def-atk) hp(for balance)
                int lost_hp = atk > def ? atk - def : def - atk;
                attackedPlayer->setHp(attackedPlayer->getHp() - lost_hp);

                cout << tmp_monster->name << " attacked " << attackedPlayer->getName()
                     << " and dealt " << lost_hp << " damage\n";
                cout << attackedPlayer->getName() << " now has " << attackedPlayer->getHp() << " hp\n";

                if (attackedPlayer->getHp() <= 0) {
                    ActionList[targetIndex].alive = false;
                    cout << attackedPlayer->getName() << " is dead.\n";
                } else {
                    displayData(*attackedPlayer);
                    getch();
                }

                // check if every player is dead
                all_player_dead = true;
                for (int i = 0; i < playerNum; i++) {
                    if (ActionList[i].alive) {
                        all_player_dead = false;
                        break;
                    }
                }
            }
            if (all_player_dead || all_monster_dead)
                break;
            turn++;
        }
    }
    if (all_player_dead)
        winner = 'm';
    else
        winner = 'p';
    cout << "The battle ended, " << winner << " team won\n";
    getch();

    // calculate exp and money
    if (winner == 'p') {
        cout << string(50, '=') << '\n';
        // get total exp
        int totalExp = 0;
        for (int i = playerNum; i < playerNum + monsterNum; i++) {
            totalExp += static_cast<BaseMonster*>(ActionList[i].instance)->exp;
        }

        // give winner players exp
        for (int i = 0; i < playerNum; i++) {
            if (ActionList[i].alive && static_cast<NovicePlayer*>(ActionList[i].instance)->getHp() > 0) {
                NovicePlayer* tmp_player = static_cast<NovicePlayer*>(ActionList[i].instance);
                tmp_player->setExp(tmp_player->getExp() + totalExp);
                cout << tmp_player->getName() << " now has " << tmp_player->getExp() << " exp\n";
            }
        }

        int totalMoney = 0;
        for (int i = playerNum; i < playerNum + monsterNum; i++) {
            totalMoney += static_cast<BaseMonster*>(ActionList[i].instance)->money;
        }

        NovicePlayer* player = static_cast<NovicePlayer*>(ActionList[0].instance);
        player->setMoney(player->getMoney() + totalMoney);
        cout << "Player team now has " << player->getMoney() << " dollars\n";
        getch();
    }
}

int Battle::getTurn() const {
    return turn;
}