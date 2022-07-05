#include <string>

#include "BaseMonster.h"

using namespace std;

#ifndef SKELETONMONSTER
#define SKELETONMONSTER
class SkeletonMonster : public BaseMonster {
   private:
   public:
    SkeletonMonster(std::string name = "Skeleton", int attack = 65, int defense = 50, int exp = 12, int money = 30, int max_hp = 100, int max_mp = 50);
    virtual std::string serialize();
    static BaseMonster* unserialize(string);
    ~SkeletonMonster() = default;
};
#endif