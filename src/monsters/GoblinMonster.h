#include <string>

#include "BaseMonster.h"
using namespace std;

#ifndef GOBLINMONSTER
#define GOBLINMONSTER
class GoblinMonster : public BaseMonster {
   private:
   public:
    GoblinMonster(std::string name = "Goblin", int attack = 60, int defense = 40, int exp = 12, int money = 30, int max_hp = 100, int max_mp = 50);
    virtual std::string serialize();
    static BaseMonster* unserialize(string);
    ~GoblinMonster() = default;
};

#endif