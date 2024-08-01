#include "hero.h"
#include "gameplaywindow.h"

Hero::Hero(Game* game, QObject *parent)
    : QObject{parent}, game_(game)
{
    heroImage_ = new QGraphicsPixmapItem(QPixmap(":/character/mobs/knight1_sword2.png"));
    heroImage_->setZValue(1);
    qreal x = heroImage_->boundingRect().width() / 2;
    qreal y = heroImage_->boundingRect().height() / 2;
    position_ = game_->gameplay_window->scene_->sceneRect().center() + QPointF(-x, -y);
    heroImage_->setPos(position_);
    game_->gameplay_window->scene_->addItem(heroImage_);
}
