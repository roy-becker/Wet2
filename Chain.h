//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_CHAIN_H
#define WET2_CHAIN_H

#include "PlayerNode.h"
#include "Player.h"

class Chain
{
private:
    PlayerNode* playerNode;

public:
    Chain* next;

    Chain(): playerNode(nullptr), next(nullptr) {}
    Chain(PlayerNode* playerNode, Chain* next): playerNode(playerNode), next(next) {}
    ~Chain();
    Chain(const Chain& other) = delete;
    Chain& operator=(const Chain& other) = delete;
    PlayerNode* getPlayerNode() const;
    PlayerNode* searchPlayer(int id) const;
    bool isDummy() const;
    void letGo();
};

#endif //WET2_CHAIN_H
