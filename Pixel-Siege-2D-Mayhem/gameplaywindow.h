#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QProgressBar>
#include <QLabel>

class Game;

class gameplayWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit gameplayWindow(Game* game, QWidget *parent = nullptr);
    ~gameplayWindow();

    void setMap(QString& map);
    QVector <QString> getMaps();
private:
    QString map_;
    QVector <QString> maps_ = {":/backgrounds/background_gameplay/grass2.png", ":/backgrounds/background_gameplay/sand.jpg"};

    Game* game_;

    QGraphicsView *view_;
    QGraphicsScene *scene_;
    QGraphicsPixmapItem *character_;
    QProgressBar* healthBar_;
    QLabel* hpLabel_;

    QPixmap hit = QPixmap(":/tools/items/hit.png");

    void Hit();
    void updateHealth(int health);

    bool facingLeft = true;
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
};

#endif // GAMEPLAYWINDOW_H
