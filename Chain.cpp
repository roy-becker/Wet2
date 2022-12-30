//
// Created by roybe on 30-Dec-22.
//

#include "Chain.h"

Chain::~Chain()
{
    //TODO add destructor :)
}

PlayerNode* Chain::getPlayerNode() const
{
    return this->playerNode;
}

Chain& Chain::operator=(const Chain& other)
{
    this->playerNode = other.playerNode;
    this->next = other.next;
}

PlayerNode* Chain::searchPlayer(int id) const
{
    if (this->playerNode->getPlayer()->getId() == id)
    {
        return this->playerNode;
    }

    if (this->next == nullptr)
    {
        return nullptr;
    }

    return this->next->searchPlayer(id);
}

bool Chain::isDummy() const
{
    return this->playerNode == nullptr;
}