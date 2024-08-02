#include "ghost.h"

Ghost::Ghost() {
    health_ = 10;
    damage_ = 2;
    facingLeft_ = false;
    speed_ = 0.6;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/ghost.png"));
}

Ghost::Ghost(const Ghost &other) : Monster(other) {}

Ghost &Ghost::operator =(const Ghost &other) {
    Monster::operator= (other);
    return *this;
}

QGraphicsPixmapItem *Ghost::getModel() {
    return model_;
}
