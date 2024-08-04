#ifndef GAME_H
#define GAME_H

#include "pause.h"
#include "authowindow.h"
#include "main_menu.h"
#include "mapchoosewindow.h"
#include "gameplaywindow.h"
#include "loginwindow.h"
#include "statswindow.h"
#include "json.hpp"
#include "monster.h"

class Hero;

class Game {
public:
    Game();
    ~Game() = default;

    void showMainMenu();
    void showLoginWindow();
    void showMapChooseWindow();
    void showPauseMenu();
    void backToMainMenu();
    void startGameplay();
    void startApplication();
    void showStatsWindow();

private:
    statsWindow* stats_window;
    loginWindow* login_window;
    AuthoWindow* autho;
    MainMenu* main_menu;
    mapChooseWindow* map_choose_window;
    gameplayWindow* gameplay_window;
    PauseMenu* pause_menu;

    Hero* hero_;
    nlohmann::json game_info;

    int senderButton = -1;

    QString currentPlayer;
    QList<Monster*> monsters_;

    friend class Hero;
    friend class PauseMenu;
    friend class gameplayWindow;
    friend class loginWindow;
    friend class AuthoWindow;

};

#endif // GAME_H
