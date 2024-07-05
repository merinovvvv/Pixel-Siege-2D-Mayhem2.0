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

private:
    qreal health_{};
    qreal damage_{};
    QGraphicsPixmapItem* model_;
    QPixmap hit_;
};

#endif // MONSTER_H
