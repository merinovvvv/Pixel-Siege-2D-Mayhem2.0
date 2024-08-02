#ifndef GHOST_H
#define GHOST_H

#include "monster.h"

class Ghost final : public Monster
{
public:
    Ghost();
    Ghost(const Ghost& other);
    Ghost& operator =(const Ghost& other);

    void move(Hero& hero) override;
};

#endif // GHOST_H
