#ifndef GHOST_H
#define GHOST_H

#include "monster.h"

class Ghost final : public Monster
{
public:
    explicit Ghost(QObject *parent = nullptr);
    Ghost();
    Ghost(const Ghost& other);
    Ghost& operator =(const Ghost& other);

    qreal getX() const override;
    qreal getY() const override;
    void setX(qreal x) override;
    void setY(qreal y) override;
};

#endif // GHOST_H
