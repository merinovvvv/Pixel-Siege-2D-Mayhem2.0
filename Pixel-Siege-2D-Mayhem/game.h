#ifndef GAME_H
#define GAME_H

#include "pause.h"

#include "main_menu.h"
#include "mapchoosewindow.h"
#include "gameplaywindow.h"
#include "monster.h"

class Hero;

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

    Hero* hero_;
    QList<Monster*> monsters;

    friend class Hero;
    friend class PauseMenu;
    friend class gameplayWindow;

};

#endif // GAME_H
