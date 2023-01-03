//
// Created by roybe on 30-Dec-22.
//

#include "Chain.h"

Chain::~Chain()
{
    if (this->playerNode != nullptr)
    {
        delete this->playerNode;
    }

    if (this->next != nullptr)
    {
        delete this->next;
    }
}

PlayerNode* Chain::getPlayerNode() const
{
    return this->playerNode;
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