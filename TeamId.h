//
// Created by roybe on 30-Dec-22.
//

#ifndef WET2_TEAMID_H
#define WET2_TEAMID_H


class TeamId
{
protected:
    int id;

public:
    explicit TeamId(int id): id(id) {}
    ~TeamId() = default;
    TeamId(const TeamId& other) = delete;
    TeamId& operator=(const TeamId& other) = delete;
    int getId() const;
    bool operator<(const TeamId& other) const;
    bool operator>(const TeamId& other) const;
    bool operator==(const TeamId& other) const;
};

#endif //WET2_TEAMID_H
