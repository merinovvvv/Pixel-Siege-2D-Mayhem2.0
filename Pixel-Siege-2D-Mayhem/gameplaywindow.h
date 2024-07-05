#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QProgressBar>
#include <QLabel>
#include <QSet>
#include <QRectF>
#include <QTime>
#include "monster.h"

class Game;

struct Models {
    QGraphicsPixmapItem* ghost_;
    QGraphicsPixmapItem* scaryGhost_;
    QGraphicsPixmapItem* skeleton_;
    QGraphicsPixmapItem* slime_;
    QGraphicsPixmapItem* wolf_;
    ~Models() = default;
};


class gameplayWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit gameplayWindow(Game* game, QWidget *parent = nullptr);
    ~gameplayWindow() = default;

    void setMap(QString& map);
    QVector <QString> getMaps();
    void spawnGhost();

private:
    QString map_;
    QVector <QString> maps_ = {":/backgrounds/background_gameplay/another_grass.png", ":/backgrounds/background_gameplay/sand.jpg"};
    QSet<int> pressedKeys_;

    Game* game_;

    QGraphicsView *view_;
    QGraphicsScene *scene_;
    QGraphicsPixmapItem *character_;
    QProgressBar* healthBar_;
    QLabel* hpLabel_;

    QPixmap hit_ = QPixmap(":/tools/items/hit.png");
    Models models_ = {
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/ghost.png")),
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/scary_ghost.png")),
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/skeleton.png")),
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/slime.png")),
        new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/wolf.png"))
    };

    Monster ghost_;
    Monster scaryGhost_;
    Monster skeleton_;
    Monster slime_;
    Monster wolf_;

    void Hit();
    void updateHealth(int health);
    QGraphicsPixmapItem *background_;
    QRectF mapBorder_;

    bool facingLeft = true;
    void updateMovement();

    QTimer* gameTime_;
    QTime startTime_;
    QLabel* showTime_;
    //QTime playerTime_;
    QTime pausedTime_;

    void pauseTimer();
    void resumeTimer();

    friend class PauseMenu;

private slots:
    void updateTimer();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMEPLAYWINDOW_H
