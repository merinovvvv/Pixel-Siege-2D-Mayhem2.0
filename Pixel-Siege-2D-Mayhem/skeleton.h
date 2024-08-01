#ifndef SKELETON_H
#define SKELETON_H

#include "monster.h"

class Skeleton final : public Monster
{
public:
    explicit Skeleton(QObject *parent = nullptr);
    Skeleton();
    Skeleton(const Skeleton& other);
    Skeleton& operator =(const Skeleton& other);

    qreal getX() const override;
    qreal getY() const override;
    void setX(qreal x) override;
    void setY(qreal y) override;
};

#endif // SKELETON_H
