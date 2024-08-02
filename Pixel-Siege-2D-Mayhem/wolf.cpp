#include "wolf.h"

Wolf::Wolf(){
    health_ = 25;
    damage_ = 5;
    facingLeft_ = true;
    speed_ = 0.8;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/wolf.png"));
}

Wolf::Wolf(const Wolf &other) : Monster(other) {}

Wolf &Wolf::operator =(const Wolf &other) {
    Monster::operator=(other);
    return *this;
}

QGraphicsPixmapItem *Wolf::getModel() {
    return model_;
}
