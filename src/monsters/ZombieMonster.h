#include "BaseMonster.h"
#include <string>

using namespace std;

#ifndef ZOMBIEMONSTER
#define ZOMBIEMONSTER
class ZombieMonster:public BaseMonster
{
private:

public:
    ZombieMonster(std::string name="Zombie",int attack=50,int defense=65,int exp=12,int money=30,int max_hp=100,int max_mp=50);
    virtual std::string serialize();
    static BaseMonster* unserialize(string);
    ~ZombieMonster()=default;
};
#endif