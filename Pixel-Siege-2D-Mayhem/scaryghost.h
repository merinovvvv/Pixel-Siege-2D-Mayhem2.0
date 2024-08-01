#ifndef SCARYGHOST_H
#define SCARYGHOST_H

#include "monster.h"

class ScaryGhost final : public Monster
{
public:
    explicit ScaryGhost(QObject *parent = nullptr);
    ScaryGhost();
    ScaryGhost(const ScaryGhost& other);
    ScaryGhost& operator =(const ScaryGhost& other);

    qreal getX() const override;
    qreal getY() const override;
    void setX(qreal x) override;
    void setY(qreal y) override;
};

#endif // SCARYGHOST_H
