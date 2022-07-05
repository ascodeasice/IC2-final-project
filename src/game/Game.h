#include <string>
#include <vector>

#include "../items/ArmorItem.h"
#include "../items/AxeWeapon.h"
#include "../items/ConsumableItem.h"
#include "../items/LifePotion.h"
#include "../items/MagicPotion.h"
#include "../items/ShieldArmor.h"
#include "../items/SwordWeapon.h"
#include "../items/TunicArmor.h"
#include "../items/WeaponItem.h"
#include "../menu/BackpackMenu.h"
#include "../menu/BattleMenu.h"
#include "../menu/FieldMenu.h"
#include "../menu/MainMenu.h"
#include "../misc/Battle.h"
#include "../misc/Field.h"
#include "../monsters/BaseMonster.h"
#include "../monsters/GoblinMonster.h"
#include "../monsters/JWMonster.h"
#include "../monsters/ZombieMonster.h"
#include "../players/KnightPlayer.h"
#include "../players/MagicianPlayer.h"
#include "../players/NovicePlayer.h"
#include "../players/OrcPlayer.h"
using namespace std;

#ifndef GAME
#define GAME
class Game {
   private:
    vector<NovicePlayer*> playerList;
    string mapName;
    int posX;
    int posY;
    int mapSize;
    int vision;
    BackpackMenu bpMenu;
    MainMenu mMenu;
    Field map;
    FieldMenu fMenu;
    vector<vector<int>> createRandomMap();
    void handleMenu();  // use main menu to decide action
    bool save();
    bool load();
    void resetArchive();  // delete archive when game ends
    bool playersAreAllDead();
   public:
    Game();  // no archive(new game)
    ~Game();
    void run();

};
#endif