#include "game.h"

Game::Game() {
    main_menu = new MainMenu();
    map_choose_window = new mapChooseWindow();
}

void Game::showMainMenu() {
    main_menu->show();
}

void Game::showMapChooseWindow() {
    main_menu->close();
    map_choose_window->show();
}

void Game::backToMainMenu() {
    map_choose_window->close();
    main_menu->show();
}

Game::~Game() {
    delete main_menu;
    delete map_choose_window;
}

