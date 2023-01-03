//
// Created by roybe on 30-Dec-22.
//

#include "Team.h"
#include "PlayerNode.h"

Team::Team(PlayerNode* node, int ability, bool goalKeeper)
{
    this->key = new TeamStats(DUMMY_ID);
    this->key->increaseAbility(ability);
    this->teamSpirit = node->getPartialSpirit();
    this->points = 0;
    this->playersTreeRoot = node;
    this->valid = goalKeeper;
    this->numPlayers = 1;
}

Team::~Team()
{
    delete this->key;
}

TeamStats* Team::getKey() const
{
    return this->key;
}

int Team::getId() const
{
    return this->key->getId();
}

int Team::getAbility() const
{
    return this->key->getAbility();
}

void Team::increaseAbility(int amount)
{
    this->key->increaseAbility(amount);
}

permutation_t Team::getTeamSpirit() const
{
    return this->teamSpirit;
}

void Team::composeTeamSpirit(const permutation_t& spirit)
{
    this->teamSpirit = this->teamSpirit * spirit;
}

int Team::getPoints() const
{
    return this->points;
}

void Team::addPoints(int amount)
{
    this->points += amount;
}

PlayerNode* Team::getPlayersTreeRoot() const
{
    return this->playersTreeRoot;
}

void Team::setPlayersTreeRoot(PlayerNode* node)
{
    this->playersTreeRoot = node;
}

bool Team::isValid() const
{
    return this->valid;
}

void Team::setValid(bool newValid)
{
    this->valid = newValid;
}

int Team::getNumPlayers() const
{
    return this->numPlayers;
}

void Team::increaseNumPlayers(int amount)
{
    this->numPlayers += amount;
}

void Team::increaseGamesPlayed(int amount)
{
    if (this->playersTreeRoot != nullptr)
    {
        this->playersTreeRoot->addGamesPlayed(amount);
    }
}

int Team::getPower() const
{
    return this->points + this->getAbility();
}

int Team::getSpiritStrength() const
{
    return this->teamSpirit.strength();
}

PlayerNode* Team::addPlayer(Player* player, int gamesPlayed, const permutation_t& spirit, int ability, bool goalKeeper)
{
    this->teamSpirit = this->teamSpirit * spirit;

    PlayerNode* node = new PlayerNode(player, gamesPlayed, this->teamSpirit, ability, goalKeeper);

    node->unionInto(this);

    return node;
}

void Team::buy(Team* other)
{
    if (this->playersTreeRoot == nullptr)
    {
        other->addPoints(this->points);

        delete other;

        return;
    }

    this->playersTreeRoot->unionInto(other);
}

bool Team::isDummy() const
{
    return this->getId() == DUMMY_ID;
}