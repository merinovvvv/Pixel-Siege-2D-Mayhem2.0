#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Monster : public QObject
{
    Q_OBJECT
public:
    explicit Monster(QObject *parent = nullptr);
    Monster(const Monster& other);
    Monster& operator =(const Monster& other);

    ~Monster() = default;

    qreal virtual getX() const = 0;
    qreal virtual getY() const = 0;
    void virtual setX(qreal x) = 0;
    void virtual setY(qreal y) = 0;
protected:
    qreal x_ = 0;
    qreal y_ = 0;
    qreal health_{};
    qreal damage_{};
    QGraphicsPixmapItem* model_;
    QPixmap hit_ = QPixmap(":/tools/items/hit.png");
};

#endif // MONSTER_H
