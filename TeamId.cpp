//
// Created by roybe on 30-Dec-22.
//

#include "TeamId.h"

int TeamId::getId() const
{
    return this->id;
}

bool TeamId::operator<(const TeamId& other) const
{
    return this->id < other.id;
}

bool TeamId::operator>(const TeamId& other) const
{
    return this->id > other.id;
}

bool TeamId::operator==(const TeamId& other) const
{
    return this->id == other.id;
}
