//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_TEAMNODE_H
#define WET2_TEAMNODE_H

//
// Created by DanielPeleg on 26/11/2022.
//

#include "OurMath.h"
#include "Team.h"
#include <iostream>

static const int LEAF_HEIGHT = 0;
static const int EMPTY_HEIGHT = -1;
static const int NUM_TEAMS_IN_EMPTY = 0;
static const int NUM_TEAMS_IN_LEAF = 1;

template <class KEY>
class TeamNode
{
private:
    Team* team;
    int height;
    int numTeamsInSubtree;

public:
    TeamNode<KEY> *left;
    TeamNode<KEY> *right;

    explicit TeamNode<KEY>(Team* team): team(team), height(LEAF_HEIGHT), left(nullptr), right(nullptr),
                                                        numTeamsInSubtree(NUM_TEAMS_IN_LEAF) {};
    TeamNode<KEY>(const TeamNode<KEY>& other) = delete;
    TeamNode<KEY>& operator=(const TeamNode<KEY>& other) = delete;
    ~TeamNode<KEY>();
    KEY* getKey() const;
    Team* getTeam() const;
    int getHeight() const;
    int getBalance() const;
    int getNumTeamsInSubtree() const;
    void setTeam(Team* newTeam);
    void updateHeight();
    void updateNumTeamsInSubtree();
    Team* searchRec(KEY* searchKey) const;
    bool isLeaf() const;
    Team* getIthTeamRec(int i) const;
    void deleteTeamsRec();
    TeamNode<KEY>* getRightMost();
    TeamNode<KEY>* getLeftMost();
};

template <class KEY>
TeamNode<KEY>::~TeamNode<KEY>()
{
    if (this->left != nullptr)
    {
        delete this->left;
    }

    if (this->right != nullptr)
    {
        delete this->right;
    }

    this->team = nullptr;
}

template <class KEY>
KEY* TeamNode<KEY>::getKey() const
{
    return this->team->getKey();
}

template <class KEY>
Team* TeamNode<KEY>::getTeam() const
{
    return this->team;
}

template <class KEY>
int TeamNode<KEY>::getHeight() const
{
    return this->height;
}

template <class KEY>
int TeamNode<KEY>::getBalance() const
{
    if ((this->left == nullptr) && (this->right== nullptr))
    {
        return 0;
    }
    else if (this->left == nullptr)
    {
        return (EMPTY_HEIGHT - this->right->height);
    }
    else if (this->right == nullptr)
    {
        return (this->left->height - EMPTY_HEIGHT);
    }
    else
    {
        return (this->left->height - this->right->height);
    }
}

template <class KEY>
int TeamNode<KEY>::getNumTeamsInSubtree() const
{
    return this->numTeamsInSubtree;
}

template <class KEY>
void TeamNode<KEY>::setTeam(Team* newTeam)
{
    this->team = newTeam;
}

template <class KEY>
void TeamNode<KEY>::updateHeight()
{
    if (this->isLeaf())
    {
        this->height = LEAF_HEIGHT;
    }
    else if (this->left == nullptr)
    {
        this->height = this->right->height + 1;
    }
    else if (this->right == nullptr)
    {
        this->height = this->left->height + 1;
    }
    else
    {
        this->height = ourMax<int>(this->left->height, this->right->height) + 1;
    }
}

template <class KEY>
void TeamNode<KEY>::updateNumTeamsInSubtree()
{
    if (this->isLeaf())
    {
        this->numTeamsInSubtree = NUM_TEAMS_IN_LEAF;
    }
    else if (this->left == nullptr)
    {
        this->numTeamsInSubtree = this->right->numTeamsInSubtree + 1;
    }
    else if (this->right == nullptr)
    {
        this->numTeamsInSubtree = this->left->numTeamsInSubtree + 1;
    }
    else
    {
        this->numTeamsInSubtree = this->right->numTeamsInSubtree + this->left->numTeamsInSubtree + 1;
    }
}

template <class KEY>
Team* TeamNode<KEY>::searchRec(KEY* searchKey) const
{
    if (*searchKey == *this->team->getKey())
    {
        return this->team;
    }
    if (*searchKey < *this->team->getKey())
    {
        if (this->left == nullptr)
        {
            return nullptr;
        }
        else
        {
            return this->left->searchRec(searchKey);
        }
    }
    else
    {
        if (this->right == nullptr)
        {
            return nullptr;
        }
        else
        {
            return this->right->searchRec(searchKey);
        }
    }
}

template <class KEY>
bool TeamNode<KEY>::isLeaf() const
{
    return this->height == LEAF_HEIGHT;
}

template <class KEY>
Team* TeamNode<KEY>::getIthTeamRec(int i) const
{
    int j;

    if (this->left == nullptr)
    {
        j = NUM_TEAMS_IN_EMPTY;
    }
    else
    {
        j = this->left->getNumTeamsInSubtree();
    }

    if (i == j)
    {
        return this->team;
    }
    if (i < j)
    {
        if (this->left == nullptr)
        {
            return nullptr;
        }
        return this->left->getIthTeamRec(i);
    }
    else
    {
        if (this->right == nullptr)
        {
            return nullptr;
        }
        return this->right->getIthTeamRec(i - j - 1);
    }
}

template <class KEY>
void TeamNode<KEY>::deleteTeamsRec()
{
    if (this->left != nullptr)
    {
        this->left->deleteTeamsRec();
    }

    if (this->right != nullptr)
    {
        this->right->deleteTeamsRec();
    }

    delete this->team;

    this->team = nullptr;
}

template <class KEY>
TeamNode<KEY>* TeamNode<KEY>::getLeftMost()
{
    if (this->left == nullptr)
    {
        return this;
    }
    else
    {
        return this->left->getLeftMost();
    }
}

template <class KEY>
TeamNode<KEY>* TeamNode<KEY>::getRightMost()
{
    if (this->right == nullptr)
    {
        return this;
    }
    else
    {
        return this->right->getRightMost();
    }
}

#endif //WET2_TEAMNODE_H
