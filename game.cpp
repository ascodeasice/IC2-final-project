#include "src/game/Game.h"

using namespace std;

/* Command for compiling and executing:

cd .\src\obj_files\
g++ ..\*\*.cpp -c
cd ..
cd ..
g++ game.cpp .\src\obj_files\*.o -o game.exe
.\game.exe

*/

int main() {
    Game RPG;
    RPG.run();
    return 0;
}
