#include "ghost.h"
#include "hero.cpp"

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

void Ghost::move() {
    model_->moveBy(5, 5);
    position_ += QPointF(5, 5);
}
