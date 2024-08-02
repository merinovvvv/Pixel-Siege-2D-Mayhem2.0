#ifndef SCARYGHOST_H
#define SCARYGHOST_H

#include "monster.h"

class ScaryGhost final : public Monster
{
public:
    ScaryGhost();
    ScaryGhost(const ScaryGhost& other);
    ScaryGhost& operator =(const ScaryGhost& other);

    QGraphicsPixmapItem* getModel() override;
};

#endif // SCARYGHOST_H
