#include <string>
#include <vector>

#include "..\items.\ArmorItem.h"
#include "..\items.\ConsumableItem.h"
#include "..\items.\Item.h"
#include "..\items.\WeaponItem.h"

using namespace std;
#ifndef NOVICEPLAYER
#define NOVICEPLAYER

class NovicePlayer {
   private:
    string name;
    int hp;   // range:[0,max ~]
    int mp;   // range:[0,max ~]
    int exp;  // NOTE won't reset to 0
   protected:
    int level;  //>=1
    int attack;
    int defense;
    int max_hp;
    int max_mp;
    int lvup_exp;
    WeaponItem* weapon;  // weapon item
    ArmorItem* armor;    // armor item

   public:
    NovicePlayer();     // level=1,name="anonymous"
    NovicePlayer(int);  // initialize level,name="anonymous"
    NovicePlayer(int, string);
    NovicePlayer(const NovicePlayer&);  // copy constructor
    static vector<Item*> backpack;
    void setName(string);
    string getName() const;
    virtual void setLevel(int);  // calculate and set atk,def,max_hp,max_mp,lvup_exp
    static int money;            //>=0
    int getLevel() const;
    void setHp(int);
    int getHp() const;
    void setMp(int);
    int getMp() const;
    void setExp(int);
    int getExp() const;
    static void setMoney(int);
    int getMoney() const;
    int getAttack() const;
    void setAttack(int);
    int getDefense() const;
    void setDefense(int);
    int getMaxHp() const;
    int getMaxMp() const;
    int getLvupExp() const;
    void setBackpackWeight(int);
    void setBackpack_weight_limit(int);
    void setBackpack_slot_limit(int);
    bool putItem(Item*);  // put item into backpack if possible
    virtual bool specialSkill();
    virtual string serialize();
    static NovicePlayer* unserialize(string);
    static int backpack_weight;        // current weight of player’s backpack
    static int backpack_weight_limit;  // limit on weight of backpack(10+level*2)
    static int backpack_slot_limit;    // limit on number of backpack’s slots(9+level)

    // NOTE these three functions should be called with takeItem()
    bool equipArmor(ArmorItem*);
    bool equipWeapon(WeaponItem*);
    bool useConsumable(ConsumableItem*);

    void displayBackpack();
    Item* takeItem(int);  // index in the backpack(start from 1)
    int getOccupiedSlot();
    int getBackpackSlotLimit() const;
    void updateBackpackWeight();  // calculate the total weights in the backpack, then set the value
    WeaponItem* getWeapon() const;
    ArmorItem* getArmor() const;
};

#endif