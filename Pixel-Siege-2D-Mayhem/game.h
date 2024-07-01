#ifndef GAME_H
#define GAME_H

#include "main_menu.h"
#include "mapchoosewindow.h"

class Game
{
public:
    Game();
    ~Game();

    MainMenu* main_menu;
    mapChooseWindow* map_choose_window;

    void showMainMenu();
    void showMapChooseWindow();
    void backToMainMenu();

private:
    QTimer* delayTimer;

private slots:
    void delayedCloseMainMenu();
    void delayedShowMainMenu();
};

#endif // GAME_H
