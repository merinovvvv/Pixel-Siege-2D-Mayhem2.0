#ifndef GAME_H
#define GAME_H

#include "main_menu.h"
#include "mapchoosewindow.h"
#include "gameplaywindow.h"
#include "gameplaywindow.h"
#include "pause.h"

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

};

#endif // GAME_H
