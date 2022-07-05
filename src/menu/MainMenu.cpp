#include "MainMenu.h"

#include <iostream>
using namespace std;

MainMenu::MainMenu() {
    name = "The curse of JW Monster";
    chosenIndex = 0;
    options = {
        "New game",
        "Load file",
        "Quit",
    };
}
