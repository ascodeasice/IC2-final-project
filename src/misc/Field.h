#include <iostream>
#include <string>
#include <vector>

#include "../menu/BackpackMenu.h"
#include "..\players\NovicePlayer.h"

using namespace std;

#ifndef Field_H
#define Field_H

// NOTE x is column, y is row use vector[y][x]

class Field {
   public:
    Field();
    // parameter: (1)the map data, (2)(3)position x, y of player, (4)(5)(width, height) of vision
    Field(vector<vector<int>>&, int, int, int, int);
    // first parameter is map name
    Field(string, int, int, int, int);
    ~Field();

    bool moveUp(void);
    bool moveDown(void);
    bool moveLeft(void);
    bool moveRight(void);
    bool move(char);

    int getCurrentPositionX(void) const;
    int getCurrentPositionY(void) const;
    int getVisionWidth(void) const;
    int getVisionHeight(void) const;
    string getMapName(void) const;
    // Parameter is the position(x, y)
    int getMapSymbol(int, int);
    // Set the position of player, parameters are position(x, y)
    void setPosition(int, int);
    // The first parameter is symbol, the rest are position(x, y)
    void setMapSymbol(int, int, int);
    // Set the size of vision, parameters are(width, height)
    void setVisionSize(int, int);
    // Displaying the map
    void display(void) const;
    bool handleEvent(int, int, int, vector<NovicePlayer*>&, BackpackMenu&);  // x,y,symbol, player, return whether the game ends

   private:
    // The actual map data with symbols and items
    vector<vector<int>> map_data;

    // x:left(0) to right, y:up(0) to down
    int current_position_x;
    int current_position_y;

    string map_name;

    int vision_width;
    int vision_height;

    int map_x_size;
    int map_y_size;
    void updateArchiveMap();  // write new info to archive map file when event is triggered
};
#endif