#include "..\misc\Field.h"
#include "BackpackMenu.h"
#include "Menu.h"
using namespace std;

#ifndef FIELDMENU
#define FIELDMENU
// class for get input for Field class
class FieldMenu : public Menu {
   private:
    Field* fieldPtr;

    Menu backpackMenu;
    vector<string> items;
    int itemIndex;

   public:
    FieldMenu();
    FieldMenu(Field&);
    bool doAction(BackpackMenu&);
    char chooseDirection();  // get W,A,S,D to move around

    // function series for backpackMenu
    void constructBackpackMenu();  // create backpackMenu from NovicePlayer::backpack
    void chooseItem();
    int getItemIndex() const;
    string getItemName(int) const;
};

#endif