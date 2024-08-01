#ifndef SLIME_H
#define SLIME_H

#include "monster.h"

class Slime final : public Monster
{
public:
    explicit Slime(QObject *parent = nullptr);
    Slime();
    Slime(const Slime& other);
    Slime& operator =(const Slime& other);

    qreal getX() const override;
    qreal getY() const override;
    void setX(qreal x) override;
    void setY(qreal y) override;
};

#endif // SLIME_H
