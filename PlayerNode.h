//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_PLAYERNODE_H
#define WET2_PLAYERNODE_H

#include "Player.h"

class Team;

class PlayerNode
{
private:
    Player* player;
    int gamesPlayedDiff;
    permutation_t partialSpiritDiff;
    Team* team;

public:
    PlayerNode* parent;

    PlayerNode(Player* player, int gamesPlayed, const permutation_t& partialSpirit): player(player), gamesPlayedDiff(gamesPlayed),
    partialSpiritDiff(partialSpirit), parent(nullptr), team(nullptr) {}
    ~PlayerNode();
    PlayerNode(const PlayerNode& other) = delete;
    PlayerNode& operator=(const PlayerNode& other) = delete;
    void unionInto(Team* newTeam);
    //void connect(PlayerNode* newParent, int gamesPlayed, const permutation_t& partialSpirit);
    Player* getPlayer() const;
    Team* getTeam() const;
    Team* findTeam() const;
    bool isRoot() const;
    int getGamesPlayed();
    permutation_t getPartialSpirit();
    PlayerNode* shrinkRoute();
    void addDegrees(PlayerNode* other);
};

#endif //WET2_PLAYERNODE_H
