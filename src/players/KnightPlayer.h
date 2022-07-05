#include "NovicePlayer.h"

using namespace std;

#ifndef KNIGHTPLAYER
#define KNIGHTPLAYER

class KnightPlayer:public NovicePlayer
{
public:
    KnightPlayer();
    KnightPlayer(int);
    KnightPlayer(int,string);
    KnightPlayer(const KnightPlayer&);
    virtual void setLevel(int);
    virtual bool specialSkill();
    virtual string serialize();
    static NovicePlayer* unserialize(string);

};

#endif