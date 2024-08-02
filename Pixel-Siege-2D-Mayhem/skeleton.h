#ifndef SKELETON_H
#define SKELETON_H

#include "monster.h"

class Skeleton final : public Monster
{
public:
    Skeleton();
    Skeleton(const Skeleton& other);
    Skeleton& operator =(const Skeleton& other);

    QGraphicsPixmapItem* getModel() override;
};

#endif // SKELETON_H
