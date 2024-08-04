#ifndef WOLF_H
#define WOLF_H

#include "monster.h"

class Wolf final : public Monster
{
public:
    Wolf();
    Wolf(const Wolf& other);
    Wolf& operator =(const Wolf& other);

    ~Wolf() = default;

    QGraphicsPixmapItem* getModel() override;
};

#endif // WOLF_H
