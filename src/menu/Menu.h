#include <string>
#include <vector>

#include "..\monsters\BaseMonster.h"
#include "..\players\NovicePlayer.h"
using namespace std;

#ifndef MENU
#define MENU
class Menu {
   private:
   protected:
    bool chosen = false;  // option has been chosen
    string name = "menu";
    vector<string> options;
    int chosenIndex = 0;  // current position of chosen option

   public:
    Menu();
    Menu(string, vector<string>&);
    void setChosenIndex(int);  // do validation for the chosen index
    virtual void display();
    virtual void chooseOption();  // change the value of chosenIndex
    int getChosenIndex() const;
};
#endif