#include "wolf.h"

Wolf::Wolf(QObject *parent) : Monster{parent} {}

Wolf::Wolf(){
    health_ = 25;
    damage_ = 5;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/wolf.png"));
}

Wolf::Wolf(const Wolf &other) : Monster(other) {}

Wolf &Wolf::operator =(const Wolf &other) {
    Monster::operator=(other);
    return *this;
}

qreal Wolf::getX() const {
    return x_;
}

qreal Wolf::getY() const {
    return y_;
}

void Wolf::setX(qreal x) {
    x_ = x;
}

void Wolf::setY(qreal y) {
    y_ = y;
}
