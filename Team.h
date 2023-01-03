//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H

#include "TeamStats.h"
#include "wet2util.h"
#include "Player.h"

class PlayerNode;

class Team
{
private:
    TeamStats* key;
    permutation_t teamSpirit;
    int points;
    PlayerNode* playersTreeRoot;
    bool valid;
    int numPlayers;

    static const int DUMMY_ID = 0;

public:
    Team(): teamSpirit(permutation_t::neutral()), points(0), playersTreeRoot(nullptr), valid(false), numPlayers(0)
    {
        this->key = new TeamStats(DUMMY_ID);
    }
    explicit Team(int id): teamSpirit(permutation_t::neutral()), points(0),
                playersTreeRoot(nullptr), valid(false), numPlayers(0)
    {
        this->key = new TeamStats(id);
    }
    Team(PlayerNode* node, int ability, bool goalKeeper);
    ~Team();
    Team(const Team& other) = delete;
    Team& operator=(const Team& other) = delete;
    TeamStats* getKey() const;
    int getId() const;
    int getAbility() const;
    void increaseAbility(int amount);
    permutation_t getTeamSpirit() const;
    void composeTeamSpirit(const permutation_t& spirit);
    int getPoints() const;
    void addPoints(int amount);
    PlayerNode* getPlayersTreeRoot() const;
    void setPlayersTreeRoot(PlayerNode* node);
    bool isValid() const;
    void setValid(bool newValid);
    int getNumPlayers() const;
    void increaseNumPlayers(int amount);
    void increaseGamesPlayed(int amount);
    int getPower() const;
    int getSpiritStrength() const;
    PlayerNode* addPlayer(Player* player, int gamesPlayed, const permutation_t& spirit, int ability, bool goalKeeper);
    void buy(Team* other);
    bool isDummy() const;
};

#endif //WET2_TEAM_H
