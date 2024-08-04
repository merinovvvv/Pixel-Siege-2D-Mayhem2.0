#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QLabel>

class Game;

class gameOverWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit gameOverWindow(Game* game, QWidget *parent = nullptr);

private slots:
    void tryAgain();
    void exit();


protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QMovie* background = new QMovie(":/backgrounds/background_menu/back7.gif");
    QPushButton* try_again_button;
    QPushButton* exit_button;
    QVBoxLayout* buttonsLayout;
    QSpacerItem* topSpacer;
    QSpacerItem* bottomSpacer;
    QWidget* centralWidget;
    QLabel* gameOverLabel;

    Game* game_;

signals:
};

#endif // GAMEOVERWINDOW_H
