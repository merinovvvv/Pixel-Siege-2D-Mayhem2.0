#ifndef GAME_H
#define GAME_H

#include "main_menu.h"
#include "mapchoosewindow.h"
<<<<<<< HEAD
#include "gameplaywindow.h"
#include "gameplaywindow.h"
=======
#include "pause.h"
>>>>>>> pause_menu

class Game
{
public:
    Game();
    ~Game();

    MainMenu* main_menu;
    mapChooseWindow* map_choose_window;
<<<<<<< HEAD
    gameplayWindow* gameplay_window;
=======
    PauseMenu* pause_menu;
>>>>>>> pause_menu

    void showMainMenu();
    void showMapChooseWindow();
    void showPauseMenu();
    void backToMainMenu();
    void startGameplay();
};

#endif // GAME_H
