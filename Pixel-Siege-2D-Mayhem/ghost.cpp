#include "ghost.h"

Ghost::Ghost() {
    health_ = 10;
    damage_ = 20;
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
