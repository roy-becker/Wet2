//
// Created by roybe on 30-Dec-22.
//

#include "PlayerTable.h"

PlayerTable::PlayerTable()
{
    this->count = 0;
    this->size = INITIAL_SIZE;
    this->table = new Chain*[this->size];
    for (int i = 0; i < this->size; ++i)
    {
        this->table[i] = nullptr;
    }
}

PlayerTable::~PlayerTable()
{
    for (int i = 0; i < this->size; ++i)
    {
        if (this->table[i] != nullptr)
        {
            delete this->table[i];
            this->table[i] = nullptr;
        }
    }

    delete[] this->table;
}

void PlayerTable::insert(PlayerNode* playerNode)
{
    ++this->count;

    int id = playerNode->getPlayer()->getId();

    int index = this->hash(id);

    this->table[index] = new Chain(playerNode, this->table[index]);

    if (this->size == this->count)
    {
        this->rehash();
    }
}

int PlayerTable::hash(int id) const
{
    return id % this->size;
}

PlayerNode* PlayerTable::member(int id)
{
    int index = this->hash(id);

    if (this->table[index] == nullptr)
    {
        return nullptr;
    }

    return table[index]->searchPlayer(id);
}

void PlayerTable::rehash()
{
    int oldSize = this->size;

    this->size = 2 * oldSize + 1;

    Chain** temp = new Chain*[this->size];
    for (int i = 0; i < this->size; ++i)
    {
        temp[i] = nullptr;
    }

    for (int i = 0; i < oldSize; ++i)
    {
        Chain* chain = this->table[i];

        Chain* toDelete;

        while (chain != nullptr)
        {
            int index = this->hash(chain->getPlayerNode()->getPlayer()->getId());
            temp[index] = new Chain(chain->getPlayerNode(), temp[index]);

            toDelete = chain;
            chain = chain->next;

            toDelete->letGo();
            delete toDelete;
        }

        this->table[i] = nullptr;
    }

    Chain** tableToDelete = this->table;

    this->table = temp;

    delete[] tableToDelete;
}