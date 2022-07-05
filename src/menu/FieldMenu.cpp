#include "FieldMenu.h"

#include <conio.h>
#include <stdlib.h>

#include <cctype>
#include <iostream>

#include "BackpackMenu.h"
using namespace std;

FieldMenu::FieldMenu() {
    ;  // do nothing
}

FieldMenu::FieldMenu(Field& field) {
    name = "Field Menu";
    fieldPtr = &field;
    chosenIndex = 0;
    options = {
        "Continue",
        "Inventory",
        "Save and Quit"};
}

// NOTE return true means end the menu
bool FieldMenu::doAction(BackpackMenu& bpMenu) {
    bool end = false;
    switch (chosenIndex) {
        case 0:
            return true;
        case 1:
            bpMenu.chooseUser();
            bpMenu.chooseOption();
            if (bpMenu.doAction())
                return true;
            else {
                getch();
                return false;
            }
        case 2:
            return true;  // Game class handle saving
        default:
            cout << "Invalid action of FieldMenu\n";
            return false;
    }
    return false;
}

char FieldMenu::chooseDirection() {
    system("cls");
    char input{};
    fieldPtr->display();
    while (true) {
        cout << "Input W,A,S,D to move, Input E to open menu:\n";
        input = getch();
        switch (toupper(input)) {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
            case 'E':  // inventory
                return input;
            default:
                cout << "Not valid move\n";
                break;
        }
    }
    return '\0';
}

int FieldMenu::getItemIndex() const {
    return itemIndex;
}

string FieldMenu::getItemName(int index) const {
    if (index < 0 || index >= items.size()) {
        cout << "Out of index of items(FieldMenu)\n";
        return "Invalid";
    }
    return items[index];
}
