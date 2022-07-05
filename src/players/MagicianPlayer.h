#include "NovicePlayer.h"

using namespace std;

#ifndef MAGICIANPLAYER
#define MAGICIANPLAYER
class MagicianPlayer:public NovicePlayer
{
public:
    MagicianPlayer();
    MagicianPlayer(int);
    MagicianPlayer(int,string);
    MagicianPlayer(const MagicianPlayer&);
    virtual void setLevel(int);
    bool specialSkill();
    virtual string serialize();
    static NovicePlayer* unserialize(string);
};

#endif