#ifndef GHOST_H
#define GHOST_H

#include "monster.h"

class Ghost final : public Monster
{
public:
    Ghost();
    Ghost(const Ghost& other);
    Ghost& operator =(const Ghost& other);

    QGraphicsPixmapItem* getModel() override;
};

#endif // GHOST_H
