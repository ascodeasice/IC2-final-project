#include <vector>

#include "../players/NovicePlayer.h"
#include "Menu.h"

using namespace std;

#ifndef BACKPACKMENU
#define BACKPACKMENU
class BackpackMenu : public Menu {
   private:
    int playerIndex;
    char action;  // D or U
    vector<NovicePlayer*> playerList;

   public:
    BackpackMenu();
    BackpackMenu(vector<NovicePlayer*>&);

    void display();
    // NOTE call it before functions using backpack
    void setOptions();                   // construct options with NovicePlayer::backpack
    void setPlayer(int, NovicePlayer*);  // set playerList[index]
    void chooseUser();                   // select user from playerList
    void chooseOption();                 // change the value of chosenIndex,and decide what to do
    bool doAction();                     // discard or use item

   public:
};
#endif