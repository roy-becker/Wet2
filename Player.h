//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H


class Player
{
private:
    int id;
    int cards;

public:
    Player(int id, int cards): id(id), cards(cards) {}
    ~Player() = default;
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;
    int getId() const;
    int getCards() const;
};


#endif //WET2_PLAYER_H
