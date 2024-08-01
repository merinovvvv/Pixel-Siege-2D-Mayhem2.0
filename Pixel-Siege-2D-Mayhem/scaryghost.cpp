#include "scaryghost.h"

ScaryGhost::ScaryGhost(QObject *parent) : Monster{parent} {}

ScaryGhost::ScaryGhost() {
    health_ = 20;
    damage_ = 4;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/scary_ghost.png"));
}

ScaryGhost::ScaryGhost(const ScaryGhost &other) : Monster(other) {}

ScaryGhost &ScaryGhost::operator =(const ScaryGhost &other){
    Monster::operator=(other);
    return *this;
}

qreal ScaryGhost::getX() const {
    return x_;
}

qreal ScaryGhost::getY() const {
    return y_;
}

void ScaryGhost::setX(qreal x) {
    x_ = x;
}

void ScaryGhost::setY(qreal y) {
    y_ = y;
}
