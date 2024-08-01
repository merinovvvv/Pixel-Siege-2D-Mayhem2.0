#include "skeleton.h"

Skeleton::Skeleton(QObject *parent) : Monster{parent} {}

Skeleton::Skeleton() {
    health_ = 5;
    damage_ = 1;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/skeleton.png"));
}

Skeleton::Skeleton(const Skeleton &other) : Monster(other){}

Skeleton &Skeleton::operator =(const Skeleton &other) {
    Monster::operator=(other);
    return *this;
}

qreal Skeleton::getX() const {
    return x_;
}

qreal Skeleton::getY() const {
    return y_;
}

void Skeleton::setX(qreal x) {
    x_ = x;
}

void Skeleton::setY(qreal y) {
    y_ = y;
}
