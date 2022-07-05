#include "Field.h"

#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#include <cctype>  //for toupper()
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../events/Event.h"
#include "../items/Item.h"
#include "../menu/BackpackMenu.h"
#include "../misc/StringProcessor.h"
#include "..\monsters\GoblinMonster.h"
#include "Battle.h"
using namespace std;

// NOTE x is column, y is row

ifstream open_ifile(string file_name) {
    ifstream ifile(file_name, ios::in);
    if (!ifile) {
        cerr << file_name << ":file not found\n";
        exit(-1);
    }
    return ifile;
}

string filter_comma(string& str) {
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',') {
            str = str.substr(i + 1);
            break;
        } else
            result += str[i];
    }
    return result;
}

Field::Field() {
    ;  // do nothing
}

Field::Field(vector<vector<int>>& map, int pos_x, int pos_y, int vw, int vh) {
    if (map.size() == 0 || map[0].size() == 0) {
        cout << "can't set map without width/height\n";
        return;
    }
    map_data = map;
    map_x_size = map_data[0].size();
    map_y_size = map_data.size();

    map_name = "dungeon";
    current_position_x = pos_x;
    current_position_y = pos_y;
    vision_width = vw;
    vision_height = vh;
}

Field::Field(string file_name, int pos_x, int pos_y, int vw, int vh) {
    ifstream map_file = open_ifile(file_name);
    string input{};
    map_file >> input;

    // column number then row number
    map_x_size = stoi(filter_comma(input));
    map_y_size = stoi(filter_comma(input));

    map_data = vector<vector<int>>(map_y_size, vector<int>(map_y_size, 0));
    // input map
    for (int row = 0; row < map_y_size; row++) {
        map_file >> input;
        for (int col = 0; col < map_x_size; col++) {
            string val = filter_comma(input);
            map_data[row][col] = stoi(val);
        }
    }

    map_name = "";
    // start from the last fifth letter(to skip .txt)
    for (int i = file_name.length() - 5; i >= 0; i--) {
        if (file_name[i] == '/' || file_name[i] == '\\')
            break;
        else
            map_name = file_name[i] + map_name;
    }
    current_position_x = pos_x;
    current_position_y = pos_y;
    vision_width = vw;
    vision_height = vh;
}

Field::~Field() {
    ;  // do nothing
}

bool Field::moveUp(void) {
    if (current_position_y - 1 >= 0) {
        current_position_y--;
        display();
        return true;
    } else {
        cout << "Unable to move up\n";
        return false;
    }
}

bool Field::moveDown(void) {
    if (current_position_y + 1 < map_y_size) {
        current_position_y++;
        display();
        return true;
    } else {
        cout << "Unable to move down\n";
        return false;
    }
}

bool Field::moveLeft(void) {
    if (current_position_x - 1 >= 0) {
        current_position_x--;
        display();
        return true;
    } else {
        cout << "Unable to move left\n";
        return false;
    }
}

bool Field::moveRight(void) {
    if (current_position_x + 1 < map_x_size) {
        current_position_x++;
        display();
        return true;
    } else {
        cout << "Unable to move right\n";
        return false;
    }
}

// return whether move is legal
bool Field::move(char direction) {
    direction = toupper(direction);

    switch (direction) {
        case 'W':
            return moveUp();
        case 'S':
            return moveDown();
        case 'A':
            return moveLeft();
        case 'D':
            return moveRight();
        case '0':
            // open menu(do nothing)
            return true;
        default:
            cout << "invalid direction input, use W,A,S,D to move\n";
            return false;
    }
    return false;
}

int Field::getCurrentPositionX(void) const {
    return current_position_x;
}

int Field::getCurrentPositionY(void) const {
    return current_position_y;
}

int Field::getVisionWidth(void) const {
    return vision_width;
}

int Field::getVisionHeight(void) const {
    return vision_height;
}

string Field::getMapName(void) const {
    return map_name;
}

int Field::getMapSymbol(int x, int y) {
    return map_data[y][x];
}

void Field::setPosition(int x, int y) {
    if (x < 0 || x >= map_x_size || y < 0 || y >= map_y_size) {
        cout << "can't set position\n";
        return;
    }
    current_position_x = x;
    current_position_y = y;
}

void Field::setMapSymbol(int x, int y, int symbol) {
    map_data[y][x] = symbol;
    updateArchiveMap();
}

void Field::setVisionSize(int width, int height) {
    vision_width = width <= 0 ? 0 : width;
    vision_height = height <= 0 ? 0 : height;
}

// Displaying the map
void Field::display(void) const {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // for colorful text

    ifstream eventFile{"./common/all_event.txt"};
    vector<char> eventSymbolList = {'O'};
    string data{};
    while (!eventFile.eof()) {
        eventFile >> data;
        data = StringProcessor::replace(data, "_", " ");
        vector<string> svec = StringProcessor::split(data, '~');
        eventSymbolList.push_back(svec[5][0]);
    }

    // read the n-th line file and get the event

    cout << "you are now at (" << current_position_x << "," << current_position_y << ") of " << map_name << " \n";
    cout << "P:player, B:battle, I:item, D:dialogue, E:the end,X:out of vision\n";
    cout << string(50, '=') << endl;
    for (int y = 0; y < map_y_size; y++) {
        for (int x = 0; x < map_x_size; x++) {
            if (x == current_position_x && y == current_position_y) {
                SetConsoleTextAttribute(hConsole, 7);  // white
                cout << "|";
                SetConsoleTextAttribute(hConsole, 14);  // yellow
                cout << "P";
            } else if (current_position_x + vision_width < x || current_position_x - vision_width > x || current_position_y + vision_height < y || current_position_y - vision_height > y) {
                SetConsoleTextAttribute(hConsole, 7);  // white
                cout << "|X";                          // out of vision
            } else if (map_data[y][x] == 0) {
                SetConsoleTextAttribute(hConsole, 7);  // white
                cout << "| ";
            } else {
                SetConsoleTextAttribute(hConsole, 7);  // white
                cout << "|";
                switch (eventSymbolList[map_data[y][x]]) {
                    case 'E':
                        SetConsoleTextAttribute(hConsole, 12);  // red
                        break;
                    case 'D':
                        SetConsoleTextAttribute(hConsole, 10);  // green
                        break;
                    case 'B':
                        SetConsoleTextAttribute(hConsole, 13);  // magenta
                        break;
                    case 'I':
                        SetConsoleTextAttribute(hConsole, 11);  // cyan
                        break;
                    default:
                        SetConsoleTextAttribute(hConsole, 7);  // white
                        break;
                }
                cout << eventSymbolList[map_data[y][x]];
            }
        }
        SetConsoleTextAttribute(hConsole, 7);
        cout << "|\n";
    }

    cout << string(50, '=') << endl;
}

// return whether the game ends
bool Field::handleEvent(int x, int y, int symbol, vector<NovicePlayer*>& playerList, BackpackMenu& bpMenu) {
    if (symbol == 0)
        return false;

    ifstream eventFile{"./common/all_event.txt"};
    string data{};

    // read the n-th line file and get the event
    for (int i = 0; i < symbol; i++) {
        eventFile >> data;
    }
    data = StringProcessor::replace(data, "_", " ");
    vector<string> svec = StringProcessor::split(data, '~');
    Event event(stoi(svec[0]), svec[1], svec[2], stoi(svec[3]), svec[4], svec[5][0], svec[6]);
    if (event.begin(playerList, bpMenu)) {
        setMapSymbol(x, y, 0);  // item is picked up, so event is triggered
    }
    if (event.type == 'E')  // end
        return true;

    display();

    return false;
}

void Field::updateArchiveMap() {
    ofstream archive{"common/archives/dungeon.txt"};
    if (!archive) {
        cout << "Can't find map archive!(Field.cpp)\n";
        getch();
        return;
    }
    archive << map_x_size << "," << map_y_size << '\n';
    for (int y = 0; y < map_y_size; y++) {
        for (int x = 0; x < map_x_size; x++) {
            archive << map_data[y][x];
            if (x != map_x_size - 1)
                archive << ",";
        }
        if (y != map_y_size - 1)
            archive << '\n';
    }
}