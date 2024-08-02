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

void Ghost::move(Hero& hero) {
    qreal dx = hero.position_.x() - position_.x();
    qreal dy = hero.position_.y() - position_.y();
    qreal length = qSqrt(dx * dx + dy * dy);

    model_->moveBy(dx / length, dy / length);
    position_ += QPointF(dx / length, dy / length);
}
