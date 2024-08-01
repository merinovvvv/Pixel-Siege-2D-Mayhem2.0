#include "monster.h"

Monster::Monster(QObject *parent) : QObject{parent} {}

Monster::Monster(qreal health, qreal damage, QGraphicsPixmapItem* model, const QPixmap &hit)
    : health_(health), damage_(damage), model_(model), hit_(hit) {}

Monster::Monster(const Monster &other) {
    class QObject;
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

qreal Monster::getHealth_() {
    return health_;
}

void Monster::setDamage(qreal& damage) {
    damage_ = damage;
}

QGraphicsPixmapItem *Monster::getModel() {
    return model_;
}
