#include "Item.h"

#include <iostream>
#include <string>

#include "ArmorItem.h"
using namespace std;

Item::Item() : name{"?"}, description{"?"}, effects{"?"}, level_required{0}, weight{0}, type{'?'} {
}

Item::Item(string name = "?", string des = "No description", string effects = "No effects", int level_required = 0, int weight = 0, char type = 'c') : name{name}, description{des}, effects{effects}, level_required{level_required}, weight{weight}, type{type} {
}

void Item::display() {
    cout << "Name:" << name << "\nDescription:"
         << description << "\nEffects:" << effects << "\nLevel required:" << level_required << "\nWeight:" << weight << "\nType:" << type << '\n';
}

string Item::serialize() {
    return "";
}