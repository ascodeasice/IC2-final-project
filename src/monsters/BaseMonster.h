#include <string>

#ifndef BASEMONSTER
#define BASEMONSTER
class BaseMonster {
   private:
    int hp;
    int mp;
    static int count;  // number of instances of monster series classes
   public:
    BaseMonster(std::string, int, int, int, int, int, int);
    ~BaseMonster();
    const std::string name;
    const int attack;
    const int defense;
    const int exp;
    const int money;
    const int max_hp;
    const int max_mp;
    static int getInstanceCount();
    virtual std::string serialize() = 0;
    void setHP(int);
    int getHP() const;
    void setMP(int);
    int getMP() const;
};
#endif