#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsPixmapItem>
#include <QtMath>

class Hero;

class Monster {
    Q_GADGET
public:
    Monster() = default;
    Monster(const Monster& other);
    Monster& operator =(const Monster& other);

    ~Monster() = default;

    qreal getX() const;
    qreal getY() const;
    QPointF getPosiotion() const;
    void setX(qreal x);
    void setY(qreal y);
    void setPosition(QPointF position);
    virtual QGraphicsPixmapItem* getModel() = 0;

    void move(Hero& hero);
protected:
    QPointF position_ = QPointF(0, 0);
    qreal health_{};
    qreal damage_{};
    QGraphicsPixmapItem* model_;
    bool facingLeft_;
    QPixmap hit_ = QPixmap(":/tools/items/hit.png");

    qreal speed_{};
};

#endif // MONSTER_H
