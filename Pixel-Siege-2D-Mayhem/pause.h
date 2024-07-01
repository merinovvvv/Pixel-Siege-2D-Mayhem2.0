#ifndef PAUSE_H
#define PAUSE_H

#include <QMainWindow>
#include <QMovie>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>

class Game;

class PauseMenu : public QMainWindow
{
    Q_OBJECT
public:
    PauseMenu(Game* game, QWidget *parent = nullptr);
    ~PauseMenu();

private slots:
    void exit();
    void back(); // this is continue but continue is a command

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMovie* background = new QMovie(":/backgrounds/background_menu/back8.gif");
    QPushButton* continue_button;
    QPushButton* exit_button;
    QVBoxLayout* buttonsLayout;
    QSpacerItem* topSpacer;
    QSpacerItem* bottomSpacer;
    QWidget* centralWidget;

    Game* game_;
};

#endif // PAUSE_H
