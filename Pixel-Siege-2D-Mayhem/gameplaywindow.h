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

class Hero;
class Game;

class gameplayWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit gameplayWindow(Game* game, QWidget *parent = nullptr);
    ~gameplayWindow() = default;

    void setMap(QString& map);
    QVector <QString> getMaps();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QString map_;
    QVector <QString> maps_ = {":/backgrounds/background_gameplay/another_grass.png", ":/backgrounds/background_gameplay/sand.jpg"};

    Game* game_;

    QGraphicsView *view_;
    QGraphicsScene *scene_;

    QProgressBar* healthBar_;
    QLabel* hpLabel_;    

    QPixmap hit_ = QPixmap(":/tools/items/hit.png");
    void Hit();
    void updateHealth(int health);

    QGraphicsPixmapItem *background_;
    QRectF mapBorder_;

    bool facingLeft = true;
    QSet<int> pressedKeys_;

    QTimer* gameTime_;
    QTime startTime_;
    QLabel* showTime_;
    QTime pausedTime_;

    QTimer* moveTimer_;
    QTimer* ghostTimer_;
    QTimer* scaryGhostTimer_;
    QTimer* skeletonTimer_;
    QTimer* slimeTimer_;
    QTimer* wolfTimer_;

    void pauseTimer();
    void resumeTimer();

    friend class PauseMenu;
    friend class Hero;

private slots:
    void updateTimer();
    void moveMonsters();
    void spawnGhost();
    void spawnScaryGhost();
    void spawnSkeleton();
    void spawnSlime();
    void spawnWolf();
};

#endif // GAMEPLAYWINDOW_H
