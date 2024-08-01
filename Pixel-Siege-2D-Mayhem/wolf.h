#ifndef WOLF_H
#define WOLF_H

#include "monster.h"

class Wolf final : public Monster
{
public:
    explicit Wolf(QObject *parent = nullptr);
    Wolf();
    Wolf(const Wolf& other);
    Wolf& operator =(const Wolf& other);

    qreal getX() const override;
    qreal getY() const override;
    void setX(qreal x) override;
    void setY(qreal y) override;
};

#endif // WOLF_H
