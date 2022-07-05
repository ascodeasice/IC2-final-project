#include "Menu.h"

#include <conio.h>
#include <stdlib.h>

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Menu::Menu() {
    options = {};
}

Menu::Menu(string name, vector<string>& options) {
    this->name = name;
    this->options.resize(options.size());
    for (int i = 0; i < options.size(); i++)
        this->options[i] = options[i];
}

void Menu::setChosenIndex(int val) {
    // moving down in the bottom will choose the top one, and vice versa
    if (val >= int(options.size()))  // NOTE must turn vector.size() (size_t) into int before comparing it to one
        chosenIndex = 0;
    else if (val < 0)
        chosenIndex = options.size() - 1;
    else
        chosenIndex = val;
}

void Menu::display() {
    system("cls");  // clear the screen
    cout << name << '\n';
    std::cout << std::string(50, '=') << std::endl;
    for (int i = 0; i < options.size(); i++) {
        if (i == chosenIndex)
            cout << "*";
        cout << options[i] << '\n';
    }
    cout << std::string(50, '=') << endl;
    cout << "Press W,S to choosen option, A to confirm\n";
}

void Menu::chooseOption() {
    char input{};

    while (!chosen) {
        display();
        input = getch();
        switch (toupper(input)) {
            case 'S':
                setChosenIndex(chosenIndex + 1);
                break;
            case 'W':
                setChosenIndex(chosenIndex - 1);
                break;
            case 'A':  // confirm
                chosen = true;
                break;
        }
    }

    chosen = false;  // reset the state
}

int Menu::getChosenIndex() const {
    return chosenIndex;
}