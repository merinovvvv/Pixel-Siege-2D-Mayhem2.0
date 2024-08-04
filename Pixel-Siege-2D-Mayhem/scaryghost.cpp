#include "scaryghost.h"

ScaryGhost::ScaryGhost() {
    health_ = 20;
    damage_ = 4;
    speed_ = 0.8;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/scary_ghost.png"));
}

ScaryGhost::ScaryGhost(const ScaryGhost &other) : Monster(other) {}

ScaryGhost &ScaryGhost::operator =(const ScaryGhost &other){
    Monster::operator=(other);
    return *this;
}

QGraphicsPixmapItem *ScaryGhost::getModel() {
    return model_;
}
