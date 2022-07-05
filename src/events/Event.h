#include <string>
#include <utility>
#include <vector>

#include "../items/Item.h"
#include "../menu/BackpackMenu.h"
#include "../players/NovicePlayer.h"

using namespace std;

#ifndef EVENT
#define EVENT
// NOTE an event can only start if the condition event is triggered
class Event {
   private:
    // rewards
    int exp_inc;
    Item* item;
    bool reward(vector<NovicePlayer*>);
    void startDialogue();  // set started to true if condition is satisfied
    void startBattle(vector<NovicePlayer*>, BackpackMenu&);
    vector<BaseMonster*> monsterList;

   public:
    const string name;
    const string dialogue;
    const int num;    // event number
    const char type;  // battle(B), dialogue(D), found item(I),Ending Event(E)
    Event(int, string, string, int, string, char, string);
    bool begin(vector<NovicePlayer*>, BackpackMenu&);
};
#endif