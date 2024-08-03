#ifndef SLIME_H
#define SLIME_H

#include "monster.h"

class Slime final : public Monster
{
public:
    Slime();
    Slime(const Slime& other);
    Slime& operator =(const Slime& other);

    ~Slime() = default;

    QGraphicsPixmapItem* getModel() override;
};

#endif // SLIME_H
