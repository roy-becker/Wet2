//
// Created by roybe on 30-Dec-22.
//

#include "PlayerNode.h"
#include "Team.h"

PlayerNode::PlayerNode(Player* player, int gamesPlayed, const permutation_t& partialSpirit, int ability, bool goalKeeper)
{
    this->player = player;
    this->gamesPlayedDiff = gamesPlayed;
    this->partialSpiritDiff = partialSpirit;
    this->parent = nullptr;

    try
    {
        this->team = new Team(this, ability, goalKeeper);
    }
    catch (const std::bad_alloc& e)
    {
        throw e;
    }
}

PlayerNode::~PlayerNode()
{
    delete this->player;
}

void PlayerNode::unionInto(Team* newTeam)
{
    Team* oldTeam = this->team;

    int n = oldTeam->getNumPlayers();
    int m = newTeam->getNumPlayers();

    PlayerNode* tree = newTeam->getPlayersTreeRoot();

    if (m == 0)
    {
        newTeam->setPlayersTreeRoot(this);
        this->team = newTeam;
    }
    else if (n <= m)
    {
        this->parent = tree;
        this->team = nullptr;

        this->gamesPlayedDiff -= tree->gamesPlayedDiff;
        this->partialSpiritDiff = tree->partialSpiritDiff.inv() *
                                    newTeam->getTeamSpirit() * partialSpiritDiff;
    }
    else
    {
        newTeam->setPlayersTreeRoot(this);
        tree->parent = this;
        this->team = newTeam;
        tree->team = nullptr;

        tree->gamesPlayedDiff -= this->gamesPlayedDiff;
        this->partialSpiritDiff = newTeam->getTeamSpirit() * this->partialSpiritDiff;
        tree->partialSpiritDiff = this->partialSpiritDiff.inv() * tree->partialSpiritDiff;
    }

    newTeam->increaseNumPlayers(n);
    newTeam->setValid(oldTeam->isValid() || newTeam->isValid());
    newTeam->increaseAbility(oldTeam->getAbility());
    newTeam->composeTeamSpirit(oldTeam->getTeamSpirit());
    newTeam->addPoints(oldTeam->getPoints());

    delete oldTeam;
}

Player* PlayerNode::getPlayer() const
{
    return this->player;
}

Team* PlayerNode::getTeam() const
{
    return this->team;
}

Team* PlayerNode::findTeam()
{
    if (this->isRoot())
    {
        return this->team;
    }

    Team* team = this->parent->findTeam();

    if (this->parent->isRoot())
    {
        return team;
    }

    this->addDegrees(this->parent);
    this->parent = this->parent->parent;

    return team;
}

bool PlayerNode::isRoot() const
{
    return this->parent == nullptr;
}

int PlayerNode::getGamesPlayed()
{
    if (this->isRoot())
    {
        return this->gamesPlayedDiff;
    }

    int gamesPlayed = this->parent->getGamesPlayed() + this->gamesPlayedDiff;

    if (this->parent->isRoot())
    {
        return gamesPlayed;
    }

    this->addDegrees(this->parent);
    this->parent = this->parent->parent;

    return gamesPlayed;
}

void PlayerNode::addGamesPlayed(int amount)
{
    this->gamesPlayedDiff += amount;
}

permutation_t PlayerNode::getPartialSpirit()
{
    if (this->isRoot())
    {
        return this->partialSpiritDiff;
    }

    permutation_t partialSpirit = this->parent->getPartialSpirit() * this->partialSpiritDiff;

    if (this->parent->isRoot())
    {
        return partialSpirit;
    }

    this->addDegrees(this->parent);
    this->parent = this->parent->parent;

    return partialSpirit;
}

PlayerNode* PlayerNode::shrinkRoute()
{
    if (this->isRoot())
    {
        return this;
    }
    if (this->parent->isRoot())
    {
        return this->parent;
    }

    PlayerNode* root = this->parent->shrinkRoute();

    this->addDegrees(this->parent);
    this->parent = root;

    return root;
}

void PlayerNode::addDegrees(PlayerNode* other)
{
    this->partialSpiritDiff = other->partialSpiritDiff * this->partialSpiritDiff;
    this->gamesPlayedDiff = other->gamesPlayedDiff + this->gamesPlayedDiff;
}