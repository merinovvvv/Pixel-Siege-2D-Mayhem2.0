#include "slime.h"

Slime::Slime(QObject *parent) : Monster{parent} {}

Slime::Slime() {
    health_ = 10;
    damage_ = 2;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/slime.png"));
}

Slime::Slime(const Slime &other) : Monster(other) {}

Slime &Slime::operator =(const Slime &other) {
    Monster::operator=(other);
    return *this;
}

qreal Slime::getX() const {
    return x_;
}

qreal Slime::getY() const {
    return y_;
}

void Slime::setX(qreal x) {
    x_ = x;
}

void Slime::setY(qreal y) {
    y_ = y;
}
