#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QVector>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Monster : public QObject {
    Q_OBJECT
public:
    explicit Monster(QObject *parent = nullptr);
    Monster(qreal health, qreal damage, QGraphicsPixmapItem* model, const QPixmap& hit);
    Monster(const Monster& other);
    Monster& operator =(const Monster& other);

    ~Monster() = default;

    qreal getHealth_();
    void setDamage(qreal& damage);
    QGraphicsPixmapItem* getModel();
    void spawnMonster();

private:
    qreal health_{};
    qreal damage_{};
    QGraphicsPixmapItem* model_;
    QPixmap hit_;
    QVector<QGraphicsPixmapItem*> models_ = {
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/ghost.png")), // ghost
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/scary_ghost.png")), // scary_ghost
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/skeleton.png")), // skeleton
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/slime.png")), // slime
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/wolf.png")) // wolf
    };
};

#endif // MONSTER_H
