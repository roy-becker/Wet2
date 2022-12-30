//
// Created by roybe on 30-Dec-22.
//

#include "TeamStats.h"

int TeamStats::getAbility() const
{
    return this->ability;
}

void TeamStats::increaseAbility(int amount)
{
    this->ability += amount;
}

bool TeamStats::operator<(const TeamStats& other) const
{
    if (this->ability < other.ability)
    {
        return true;
    }
    if (this->ability > other.ability)
    {
        return false;
    }

    return this->id < other.id;
}

bool TeamStats::operator>(const TeamStats& other) const
{
    return other < *this;
}

bool TeamStats::operator==(const TeamStats& other) const
{
    return (this->id == other.id) && (this->ability == other.ability);
}
