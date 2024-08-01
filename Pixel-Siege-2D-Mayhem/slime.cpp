#include "slime.h"

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
