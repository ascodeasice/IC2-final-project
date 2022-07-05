#include "BaseMonster.h"
#include <string>

using namespace std;
#ifndef JWMONSTER
#define JWMONSTER
class JWMonster:public BaseMonster 
{
private:

public:
    JWMonster(std::string name="JWMonster",int attack=400,int defense=400,int exp=42,int money=175,int max_hp=500,int max_mp=100);
    virtual std::string serialize();
    static BaseMonster* unserialize(string);
    ~JWMonster()=default;
};
#endif