#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QSet>
#include <QRectF>

class Game;

class gameplayWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit gameplayWindow(Game* game, QWidget *parent = nullptr);
    ~gameplayWindow() = default;

    void setMap(QString& map);
    QVector <QString> getMaps();
private:
    QString map_;
    QVector <QString> maps_ = {":/backgrounds/background_gameplay/another_grass.png", ":/backgrounds/background_gameplay/sand.jpg"};
    QSet<int> pressedKeys_;

    Game* game_;

    QGraphicsView *view_;
    QGraphicsScene *scene_;
    QGraphicsPixmapItem *character_;
    QGraphicsPixmapItem *background_;
    QRectF mapBorder_;

    bool facingLeft = true;
    void updateMovement();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMEPLAYWINDOW_H
