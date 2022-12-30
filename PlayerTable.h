//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_PLAYERTABLE_H
#define WET2_PLAYERTABLE_H

#include "Chain.h"

class PlayerTable
{
private:
    Chain** table;
    int size;
    int count;
    static const int INITIAL_SIZE = 63;

public:
    PlayerTable();
    ~PlayerTable();
    PlayerTable(const PlayerTable& other) = delete;
    PlayerTable& operator=(const PlayerTable& other) = delete;
    void insert(PlayerNode* playerNode);
    int hash(int id) const;
    PlayerNode* member(int id);
    void rehash();
};


#endif //WET2_PLAYERTABLE_H
