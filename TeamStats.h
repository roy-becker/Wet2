//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_TEAMSTATS_H
#define WET2_TEAMSTATS_H

#include "TeamId.h"

class TeamStats: public TeamId
{
private:
    int ability;

public:
    explicit TeamStats(int id): TeamId(id), ability(0) {}
    ~TeamStats() = default;
    TeamStats(const TeamStats& other) = delete;
    TeamStats& operator=(const TeamStats& other) = delete;
    int getAbility() const;
    void increaseAbility(int amount);
    bool operator<(const TeamStats& other) const;
    bool operator>(const TeamStats& other) const;
    bool operator==(const TeamStats& other) const;
};

#endif //WET2_TEAMSTATS_H
