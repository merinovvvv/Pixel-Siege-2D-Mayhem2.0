#ifndef GAME_H
#define GAME_H

#include "pause.h"

#include "main_menu.h"
#include "mapchoosewindow.h"
#include "gameplaywindow.h"

class Game {
public:
    Game();
    ~Game() = default;

    void showMainMenu();
    void showMapChooseWindow();
    void showPauseMenu();
    void backToMainMenu();
    void startGameplay();

private:
    MainMenu* main_menu;
    mapChooseWindow* map_choose_window;
    gameplayWindow* gameplay_window;
    PauseMenu* pause_menu;

    friend class PauseMenu;

};

#endif // GAME_H
