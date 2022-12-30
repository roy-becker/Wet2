//
// Created by roybe on 30-Dec-22.
//

#include "PlayerNode.h"
#include "Team.h"

PlayerNode::~PlayerNode()
{
    //TODO add destructor :)
}

void PlayerNode::unionInto(Team* newTeam)
{
    int n = this->team->getNumPlayers();
    int m = newTeam->getNumPlayers();

    PlayerNode* tree = newTeam->getPlayersTreeRoot();

    if (m == 0)
    {
        newTeam->setPlayersTreeRoot(this);
    }
    else if (n < m)
    {
        this->parent = tree;

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
    newTeam->setValid(this->team->isValid() || newTeam->isValid());
    newTeam->increaseAbility(this->team->getAbility());
    newTeam->composeTeamSpirit(this->team->getTeamSpirit());
    newTeam->addPoints(this->team->getPoints());
}

Player* PlayerNode::getPlayer() const
{
    return this->player;
}

Team* PlayerNode::getTeam() const
{
    return this->team;
}

Team* PlayerNode::findTeam() const
{
    if (this->isRoot())
    {
        return this->team;
    }

    return this->parent->findTeam();
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

    return this->parent->getGamesPlayed() + this->gamesPlayedDiff;
}

permutation_t PlayerNode::getPartialSpirit()
{
    if (this->isRoot())
    {
        return this->partialSpiritDiff;
    }

    return this->parent->getPartialSpirit() * this->partialSpiritDiff;
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