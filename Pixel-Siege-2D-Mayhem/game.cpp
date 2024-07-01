#include "game.h"

Game::Game() {
    main_menu = new MainMenu(this);
    map_choose_window = new mapChooseWindow(this);
    pause_menu = new PauseMenu(this);
}

void Game::showMainMenu() {
    main_menu->show();
    map_choose_window->close();
    pause_menu->close();
}

void Game::showMapChooseWindow() {
    map_choose_window->showFullScreen();
    main_menu->close();
    pause_menu->close();
}

void Game::showPauseMenu() {
    pause_menu->showFullScreen();
}

void Game::backToMainMenu() {
    main_menu->show();
    map_choose_window->close();
}

Game::~Game() {
    delete main_menu;
    delete map_choose_window;
}
