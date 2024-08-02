#include "monster.h"
#include "hero.cpp"

Monster::Monster(const Monster &other) {
    health_ = other.health_;
    damage_ = other.damage_;
    model_ = other.model_;
    facingLeft_ = other.facingLeft_;
    hit_ = other.hit_;
}

Monster &Monster::operator =(const Monster &other) {
    if (&other == this) {
        return *this;
    }
    health_ = other.health_;
    damage_ = other.damage_;
    model_ = other.model_;
    facingLeft_ = other.facingLeft_;
    hit_ = other.hit_;
    return *this;
}

qreal Monster::getX() const {
    return position_.x();
}

qreal Monster::getY() const {
    return position_.y();
}

QPointF Monster::getPosiotion() const{
    return position_;
}

void Monster::setX(qreal x) {
    position_.setX(x);
}

void Monster::setY(qreal y) {
    position_.setY(y);
}

void Monster::setPosition(QPointF position) {
    position_ = position;
}

void Monster::move(Hero &hero) {
    qreal dx = hero.position_.x() - position_.x();
    qreal dy = hero.position_.y() - position_.y();
    qreal length = qSqrt(dx * dx + dy * dy);

    if (dx < 0 && !facingLeft_) {
        facingLeft_ = true;
        model_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
    }
    if (dx > 0 && facingLeft_){
        facingLeft_ = false;
        model_->setTransform(QTransform(-1, 0, 0, 1, model_->boundingRect().width(), 0));
    }

    model_->moveBy(dx / length, dy / length);
    position_ += QPointF(dx / length * speed_, dy / length * speed_);
}
