//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_TEAMTREE_H
#define WET2_TEAMTREE_H

//
// Created by DanielPeleg on 26/11/2022.
//

#include "Team.h"
#include "TeamNode.h"
#include <iostream>

template <class KEY>
class TeamTree
{
private:
    static TeamNode<KEY>* rotateLL(TeamNode<KEY>* B);
    static TeamNode<KEY>* rotateRR(TeamNode<KEY>* A);
    static TeamNode<KEY>* rotateLR(TeamNode<KEY>* C);
    static TeamNode<KEY>* rotateRL(TeamNode<KEY>* A);
    static TeamNode<KEY>* rebalance(TeamNode<KEY>* node);
    static TeamNode<KEY>* insertRec(TeamNode<KEY>* node,Team* team);
    static TeamNode<KEY>* removeRec(TeamNode<KEY>* node,Team* team);
    static bool isAVLTree(TeamNode<KEY>* node);

public:
    TeamNode<KEY>* tree;

    TeamTree<KEY>(): tree(nullptr) {};
    ~TeamTree<KEY>();
    TeamTree<KEY>(const TeamTree<KEY>& other) = delete;
    TeamTree<KEY>& operator=(const TeamTree<KEY>& other) = delete;
    Team* search(KEY* searchKey);
    void insert(Team* team);
    void remove(Team* team);
    Team* getIthTeam(int i) const;
    bool isAVLTree() const;
    void deleteTeams();
};

template <class KEY>
TeamTree<KEY>::~TeamTree<KEY>()
{
    if (this->tree != nullptr)
    {
        delete this->tree;
    }
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::rotateLL(TeamNode<KEY>* B)
{
    TeamNode<KEY> *A = B->left;
    TeamNode<KEY> *AR = A->right;

    A->right = B;
    B->left = AR;

    B->updateHeight();
    A->updateHeight();

    B->updateNumTeamsInSubtree();
    A->updateNumTeamsInSubtree();

    return A;
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::rotateRR(TeamNode<KEY>* A)
{
    TeamNode<KEY> *B = A->right;
    TeamNode<KEY> *BL = B->left;

    B->left = A;
    A->right = BL;

    A->updateHeight();
    B->updateHeight();

    A->updateNumTeamsInSubtree();
    B->updateNumTeamsInSubtree();

    return B;
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::rotateLR(TeamNode<KEY>* C)
{
    C->left = rotateRR(C->left);
    return rotateLL(C);
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::rotateRL(TeamNode<KEY>* A)
{
    A->right = rotateLL(A->right);
    return rotateRR(A);
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::rebalance(TeamNode<KEY>* node)
{
    int balance = node->getBalance();

    if (balance > 1)
    {
        if (node->left->getBalance() > -1)
        {
            return rotateLL(node);
        }
        else if (node->left->getBalance() == -1)
        {
            return rotateLR(node);
        }
    }
    else if (balance < -1)
    {
        if (node->right->getBalance() < 1)
        {
            return rotateRR(node);
        }
        else if (node->right->getBalance() == 1)
        {
            return rotateRL(node);
        }
    }

    return node;
}

template <class KEY>
Team* TeamTree<KEY>::search(KEY* searchKey)
{
    if (this->tree == nullptr)
    {
        return nullptr;
    }
    return this->tree->searchRec(searchKey);
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::insertRec(TeamNode<KEY>* node, Team* team)
{
    if (node == nullptr)
    {
        return (new TeamNode<KEY>(team));
    }

    KEY* key = team->getKey();

    if (*key < *(node->getKey()))
    {
        node->left = insertRec(node->left, team);
    }
    else if (*key > *(node->getKey()))
    {
        node->right = insertRec(node->right, team);
    }
    else
    {
        return node;
    }

    node->updateHeight();
    node->updateNumTeamsInSubtree();

    return rebalance(node);
}

template <class KEY>
void TeamTree<KEY>::insert(Team* team)
{
    this->tree = insertRec(this->tree, team);
}

template <class KEY>
TeamNode<KEY>* TeamTree<KEY>::removeRec(TeamNode<KEY>* node, Team* team)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    KEY* key = team->getKey();

    TeamNode<KEY>* neighbor;

    if(*key < *node->getKey())
    {
        node->left = removeRec(node->left,team);
    }
    else if(*key > *node->getKey())
    {
        node->right = removeRec(node->right,team);
    }
    else
    {
        if (node->left != nullptr)
        {
            neighbor = node->left->getRightMost();
            Team* newTeam = neighbor->getTeam();
            node->setTeam(newTeam);

            node->left = removeRec(node->left, newTeam);
        }
        else if (node->right != nullptr)
        {
            neighbor = node->right->getLeftMost();
            Team* newTeam = neighbor->getTeam();
            node->setTeam(newTeam);

            node->right = removeRec(node->right, newTeam);
        }
        else
        {
            delete node;
            return nullptr;
        }
    }

    node->updateHeight();
    node->updateNumTeamsInSubtree();

    return rebalance(node);
}

template <class KEY>
void TeamTree<KEY>::remove(Team* team)
{
    this->tree = removeRec(this->tree,team);
}

template <class KEY>
Team* TeamTree<KEY>::getIthTeam(int i) const
{
    if (this->tree == nullptr)
    {
        return nullptr;
    }
    return this->tree->getIthTeamRec(i);
}

template <class KEY>
bool TeamTree<KEY>::isAVLTree(TeamNode<KEY>* node)
{
    if (node == nullptr)
    {
        return true;
    }
    return ((-1 <= node->getBalance()) && (node->getBalance() <= 1) && isAVLTree(node->right) && isAVLTree(node->left));
}

template <class KEY>
bool TeamTree<KEY>::isAVLTree() const
{
    return isAVLTree(this->tree);
}

template <class KEY>
void TeamTree<KEY>::deleteTeams()
{
    if (this->tree != nullptr)
    {
        this->tree->deleteTeamsRec();
    }
}

#endif //WET2_TEAMTREE_H
