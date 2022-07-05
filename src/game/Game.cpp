#include "Game.h"

#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <fstream>
#include <iostream>
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
#include "..\menu\BackpackMenu.h"
#include "..\menu\BattleMenu.h"
#include "..\menu\FieldMenu.h"
#include "..\menu\MainMenu.h"
#include "..\menu\Menu.h"

using namespace std;

// new game
Game::Game() {
    srand(time(NULL));
    playerList = {
        new KnightPlayer(1, "KnightPlayer"),
        new OrcPlayer(1, "OrcPlayer"),
        new MagicianPlayer(1, "MagicianPlayer")};
    posX = 0;
    posY = 0;
    vision = 1;
    mapName = "dungeon";
    bpMenu = BackpackMenu(playerList);
    mapSize = 10;
    createRandomMap();

    mMenu = MainMenu();
}

Game::~Game() {
    for (auto& player : playerList) {
        delete player;
    }
}

void Game::handleMenu() {
    bool valid = false;
    while (valid == false) {
        mMenu.chooseOption();
        switch (mMenu.getChosenIndex()) {
            case 0: {  // new game
                valid = true;
                vector<string> mapOptions = {"small", "medium", "large"};
                Menu mapMenu = Menu("Map size", mapOptions);
                mapMenu.chooseOption();
                switch (mapMenu.getChosenIndex()) {
                    case 0:
                        mapSize = 10;
                        break;
                    case 1:
                        mapSize = 15;
                        break;
                    case 2:
                        mapSize = 20;
                        break;
                }
                createRandomMap();
                break;
            }
            case 1:
                if (load()) {
                    valid = true;
                }
                break;
            case 2:
                cout << "Quitting...\n";
                exit(0);
            default:
                cout << "Undefined behavior\n";
                break;
        }
    }
}

vector<vector<int>> Game::createRandomMap() {
    const int itemEventNum = 40;
    const int normalItemNum = 17;
    const int rareItemNum = 10;
    const int veryRareItemNum = 13;
    const int battleNum = 15;
    const int eventNum = 107;
    const int otherEventNum = 51;

    vector<vector<int>> randomMap(mapSize, vector<int>(mapSize, 0));  // NOTE % event number

    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            int prob = rand() % 100;
            if (prob < 20)  // NOTE 20% nothing
                continue;
            else if (prob < 60) {  // 40% of battles
                randomMap[i][j] = itemEventNum + 1 + rand() % battleNum;
            } else if (prob < 90) {  // 30% of items
                int itemProb = rand() % 100;
                if (itemProb < 70) {  // 70% of normal items
                    randomMap[i][j] = rand() % normalItemNum;
                } else if (itemProb < 90) {  // 20% of rare items
                    randomMap[i][j] = normalItemNum + 1 + rand() % rareItemNum;
                } else {  // 10% of very rare items
                    randomMap[i][j] = normalItemNum + rareItemNum + 1 + rand() % veryRareItemNum;
                }
            } else {  // 10% of dialogue
                randomMap[i][j] = itemEventNum + battleNum + 1 + rand() % otherEventNum;
            }
        }
    }
    randomMap[0][0] = eventNum + 1;                  // the start will not have event
    randomMap[mapSize - 1][mapSize - 1] = eventNum;  // the last event is the boss battle
    map = Field(randomMap, posX, posY, vision, vision);
    fMenu = FieldMenu(map);

    return randomMap;
}

void Game::run() {
    handleMenu();

    map.handleEvent(posX, posY, map.getMapSymbol(posX, posY), playerList, bpMenu);

    char action{};
    while (playersAreAllDead() == false) {
        action = fMenu.chooseDirection();
        if (toupper(action) == 'E') {  // open menu
            fMenu.chooseOption();
            fMenu.doAction(bpMenu);
            if (fMenu.getChosenIndex() == 2) {  // save game
                if (save()) {
                    cout << "Quitting...\n";
                    exit(0);
                }
            }
        } else
            map.move(action);

        posX = map.getCurrentPositionX();
        posY = map.getCurrentPositionY();
        int eventSymbol = map.getMapSymbol(posX, posY);
        if (map.handleEvent(posX, posY, eventSymbol, playerList, bpMenu))
            break;  // the game ends
    }

    // SECTION game ends
    resetArchive();
    if (playersAreAllDead()) {
        system("cls");
        cout << "You were defeated, now people will suffer from the curse of JW monster... forever\n";
    } else {
        system("cls");
        cout << "Game over, you defeated the JW Monster, people is now free again\n";
        cout << "You earned: " << NovicePlayer::money << " dollars\n";
    }

    // pause the screen
    getch();
}

// NOTE read from game.exe
bool Game::save() {
    ofstream playerFile("./common/archives/players.txt");
    ofstream itemFile("./common/archives/items.txt");
    ofstream infoFile("./common/archives/info.txt");
    ofstream equipmentFile("./common/archives/equipment.txt");

    if (!playerFile || !itemFile || !infoFile || !equipmentFile) {
        cout << "Can't save file\n";
        getch();
        return false;
    }
    for (auto& player : playerList) {
        playerFile << player->serialize() << '\n';
        WeaponItem* weapon = player->getWeapon();
        ArmorItem* armor = player->getArmor();
        equipmentFile << (weapon == nullptr ? "None" : weapon->serialize()) << '\n';
        equipmentFile << (armor == nullptr ? "None" : armor->serialize()) << '\n';
    }

    for (auto& item : NovicePlayer::backpack) {
        if (item == nullptr)
            continue;
        itemFile << item->serialize() << '\n';
    }

    infoFile << to_string(NovicePlayer::money) << '\n';
    infoFile << mapName << '\n';
    infoFile << posX << '\n';
    infoFile << posY << '\n';
    infoFile << vision << '\n';

    cout << "File saved!\n";
    getch();
    return true;
}

bool Game::load() {
    ifstream playerFile("./common/archives/players.txt");
    ifstream itemFile("./common/archives/items.txt");
    ifstream infoFile("./common/archives/info.txt");
    ifstream equipmentFile("./common/archives/equipment.txt");

    if (!playerFile || !itemFile || !infoFile || !equipmentFile) {
        cout << "Can't load file\n";
        getch();
        return false;
    }
    // SECTION player
    if (playerFile.peek() == std::ifstream::traits_type::eof()) {  // file is empty
        system("cls");
        cout << "Can't load file\n";
        getch();
        return false;
    }
    playerList.clear();
    int playerIndex = 0;
    while (playerFile) {
        string str{};

        playerFile >> str;
        if (str == "")
            break;
        switch (str[0]) {
            case 'N':
                playerList.resize(playerIndex + 1);
                playerList[playerIndex++] = NovicePlayer::unserialize(str);
                break;
            case 'K':
                playerList.resize(playerIndex + 1);
                playerList[playerIndex++] = KnightPlayer::unserialize(str);
                break;
            case 'O':
                playerList.resize(playerIndex + 1);
                playerList[playerIndex++] = OrcPlayer::unserialize(str);
                break;
            case 'M':
                playerList.resize(playerIndex + 1);
                playerList[playerIndex++] = MagicianPlayer::unserialize(str);
                break;
            default:
                break;
        }
    }
    bpMenu = BackpackMenu(playerList);

    // SECTION equipments
    int index = 0;
    while (!equipmentFile.eof()) {
        string str{};
        equipmentFile >> str;
        if (str != "None" && str != "") {
            if (index % 2 == 0) {
                playerList[floor(index / 2)]->equipWeapon(dynamic_cast<WeaponItem*>(WeaponItem::unserialize(str)));
            } else {
                playerList[floor(index / 2)]->equipArmor(dynamic_cast<ArmorItem*>(ArmorItem::unserialize(str)));
            }
        }
        index++;
    }

    // SECTION items
    while (!itemFile.eof()) {
        string str{};
        itemFile >> str;
        if (str != "") {
            switch (str[0]) {
                case 'A':
                    playerList[0]->putItem(ArmorItem::unserialize(str));
                    break;
                case 'W':
                    playerList[0]->putItem(WeaponItem::unserialize(str));
                    break;
                case 'C':
                    playerList[0]->putItem(ConsumableItem::unserialize(str));
                    break;
                default:
                    break;
            }
        }
    }
    try {
        string str{};
        infoFile >> str;
        NovicePlayer::setMoney(stoi(str));
        infoFile >> str;
        mapName = str;
        infoFile >> str;
        posX = stoi(str);
        infoFile >> str;
        posY = stoi(str);
        infoFile >> str;
        vision = stoi(str);
    } catch (...) {
        cout << "Can't load file\n";
        getch();
        return false;
    }
    map = Field("common/archives/dungeon.txt", posX, posY, vision, vision);
    fMenu = FieldMenu(map);

    return true;
}

bool Game::playersAreAllDead() {
    for (auto& player : playerList) {
        if (player->getHp() > 0) {
            return false;
        }
    }
    return true;
}

void Game::resetArchive() {
    // truncate those files
    ofstream playerFile("./common/archives/players.txt");
    ofstream itemFile("./common/archives/items.txt");
    ofstream infoFile("./common/archives/info.txt");
    ofstream equipmentFile("./common/archives/equipment.txt");
    ofstream archiveMap("common/archives/dungeon.txt");
}