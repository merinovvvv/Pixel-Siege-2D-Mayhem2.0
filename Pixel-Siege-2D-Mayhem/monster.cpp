#include "monster.h"

Monster::Monster(QObject *parent) : QObject{parent} {}

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
