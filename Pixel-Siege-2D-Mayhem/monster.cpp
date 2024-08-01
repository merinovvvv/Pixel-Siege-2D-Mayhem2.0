#include "monster.h"

Monster::Monster(const Monster &other) {
    health_ = other.health_;
    damage_ = other.damage_;
    model_ = other.model_;
    hit_ = other.hit_;
}

Monster &Monster::operator =(const Monster &other) {
    if (&other == this) {
        return *this;
    }
    health_ = other.health_;
    damage_ = other.damage_;
    model_ = other.model_;
    hit_ = other.hit_;
    return *this;
}

qreal Monster::getX() const {
    return position_.x();
}

qreal Monster::getY() const {
    return position_.y();
}

QPointF Monster::getPosiotion() const{
    return position_;
}

void Monster::setX(qreal x) {
    position_.setX(x);
}

void Monster::setY(qreal y) {
    position_.setY(y);
}

void Monster::setPosition(QPointF position) {
    position_ = position;
}

QGraphicsPixmapItem *Monster::getModel() {
    return model_;
}
