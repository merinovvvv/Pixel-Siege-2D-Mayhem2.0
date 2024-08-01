#ifndef SCARYGHOST_H
#define SCARYGHOST_H

#include "monster.h"

class ScaryGhost final : public Monster
{
public:
    ScaryGhost();
    ScaryGhost(const ScaryGhost& other);
    ScaryGhost& operator =(const ScaryGhost& other);
};

#endif // SCARYGHOST_H
