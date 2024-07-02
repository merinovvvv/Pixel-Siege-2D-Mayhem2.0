#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QMainWindow>
#include <QMovie>
#include <QPaintEvent>
#include <QPushButton>
#include <QSpacerItem>
#include <QLayout>

class Game;

class MainMenu : public QMainWindow {
    Q_OBJECT

public:
    MainMenu(Game* game, QWidget *parent = nullptr);
    ~MainMenu();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void exitSlot();
    void showMapChooseWindow();

private:
    QMovie *background = new QMovie(":/backgrounds/background_menu/back6.gif");
    QWidget* centralWidget;
    QSpacerItem* leftSpacer;
    QSpacerItem* rightSpacer;
    QPushButton* startButton;
    QPushButton* statsButton;
    QPushButton* achievementsButton;
    QPushButton* exitButton;
    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;

    Game* game_;
};
#endif // MAIN_MENU_H
