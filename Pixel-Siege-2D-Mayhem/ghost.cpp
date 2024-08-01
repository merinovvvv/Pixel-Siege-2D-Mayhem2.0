#include "ghost.h"

Ghost::Ghost(QObject *parent) : Monster{parent} {}

Ghost::Ghost() {
    health_ = 10;
    damage_ = 2;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/ghost.png"));
}

Ghost::Ghost(const Ghost &other) : Monster(other) {}

Ghost &Ghost::operator =(const Ghost &other) {
    Monster::operator= (other);
    return *this;
}

qreal Ghost::getX() const {
    return x_;
}

qreal Ghost::getY() const {
    return y_;
}

void Ghost::setX(qreal x) {
    x_ = x;
}

void Ghost::setY(qreal y) {
    y_ = y;
}
