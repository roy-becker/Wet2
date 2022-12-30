//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H

#include "TeamStats.h"
#include "wet2util.h"
#include "PlayerNode.h"

class Team
{
private:
    TeamStats* key;
    permutation_t teamSpirit;
    int points;
    PlayerNode* playersTreeRoot;
    bool hasGoalKeeper;
    int numPlayers;

public:
    Team(): key() {}
    ~Team();
    TeamStats* getKey() const;

};


#endif //WET2_TEAM_H
