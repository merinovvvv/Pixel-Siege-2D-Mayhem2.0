#ifndef GAME_H
#define GAME_H

#include "main_menu.h"
#include "mapchoosewindow.h"
#include "pause.h"

class Game
{
public:
    Game();
    ~Game();

    MainMenu* main_menu;
    mapChooseWindow* map_choose_window;
    PauseMenu* pause_menu;

    void showMainMenu();
    void showMapChooseWindow();
    void showPauseMenu();
    void backToMainMenu();
};

#endif // GAME_H
