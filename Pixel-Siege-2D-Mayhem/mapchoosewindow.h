#ifndef MAPCHOOSEWINDOW_H
#define MAPCHOOSEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMovie>
#include <QPainter>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

class Game;


class mapChooseWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit mapChooseWindow(Game* game, QWidget *parent = nullptr);
    ~mapChooseWindow() = default;

    QPixmap getMapBack();
    QVector <QPixmap> getMapsForChoose();

private slots:
    void backToMainMenu();
    void changeMap();
    void startGame();

private:
    QPushButton *backButton;
    QLabel* chooseMap;
    QMovie *mapChooseBackground;
    QGraphicsScene* mapChooseScene;
    QGraphicsView* mapChooseView;
    QGraphicsRectItem* mapItem;
    QPixmap mapBack;
    QVector <QPixmap> mapsForChoose;
    QPushButton* startButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    int currentIndex = 0;

    Game* game_;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAPCHOOSEWINDOW_H
