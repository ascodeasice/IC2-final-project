#include "NovicePlayer.h"

using namespace std;

#ifndef ORCPLAYER
#define ORCPLAYER

class OrcPlayer:public NovicePlayer
{
public:
    OrcPlayer();
    OrcPlayer(int);
    OrcPlayer(int,string);
    OrcPlayer(const OrcPlayer&);
    virtual void setLevel(int);
    bool specialSkill();
    virtual string serialize();
    static NovicePlayer* unserialize(string);
};

#endif