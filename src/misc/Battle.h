#include <iostream>

#include "..\menu\BackpackMenu.h"
#include "..\menu\BattleMenu.h"
#include "..\monsters\BaseMonster.h"
#include "..\players\NovicePlayer.h"
#ifndef BATTLE
#define BATTLE

struct Character {
    char type;       // monster or player?
    bool alive;      // alive or dead?
    void *instance;  // pointer to instance
};

class Battle {
   private:
    BattleMenu menu;
    Character *ActionList;  // NOTE there are "playerNum" players in the front, then "monsterNum" monsters
    int playerNum;
    int monsterNum;
    int turn;     // total actions every character has done
    char winner;  // p or m

   public:
    Battle(int, int);  // construct array of characters
    ~Battle();
    void setPlayer(int, NovicePlayer *);  // set character in actionList by index
    void setMonster(int, BaseMonster *);
    void determineOrder();
    void displayData(const BaseMonster &) const;
    void displayData(const NovicePlayer &) const;
    void begin(BackpackMenu &);  // begin the battle
    char getWinner() const;
    // void displayActionList() const;
    int getTurn() const;
};

#endif