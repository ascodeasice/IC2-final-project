#include <string>

using namespace std;
#ifndef ITEM
#define ITEM
class Item {
   public:
    Item();
    Item(string, string, string, int, int, char);
    const string name;
    const string description;
    const string effects;
    const int level_required;
    const int weight;
    const char type;  // w, a, c
    virtual string serialize();
    Item* unserialize(string);
    void display();
};

#endif