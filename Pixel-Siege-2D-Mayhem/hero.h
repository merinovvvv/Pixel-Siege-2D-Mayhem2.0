#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "game.h"

class Hero : public QObject {
    Q_OBJECT
public:
    explicit Hero(Game* game, QObject *parent = nullptr);

private:
    Game* game_;
    QPointF position_;

    QGraphicsPixmapItem *heroImage_;
    void updateHealth(int health);

    friend class gameplayWindow;
    friend class Game;
    friend class Monster;
};

#endif // HERO_H
