#include <string>
#include <vector>

#include "..\monsters\BaseMonster.h"
#include "..\players\NovicePlayer.h"
#include "BackpackMenu.h"
#include "Menu.h"

using namespace std;

#ifndef BATTLEMENU
#define BATTLEMENU
class BattleMenu : public Menu {
   private:
    Menu targetMenu;
    vector<string> targets;
    int targetIndex;

    Menu backpackMenu;
    vector<string> items;
    int itemIndex;

   public:
    BattleMenu();
    bool doAction(NovicePlayer*, BaseMonster*, BackpackMenu&);

    // function series for targetMenu
    void setTarget(int, string);  // index and name of enemies
    void chooseTarget();
    int getTargetIndex() const;
    string getTargetName(int) const;
};
#endif