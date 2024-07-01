#include "game.h"

Game::Game() {
    main_menu = new MainMenu(this);
    map_choose_window = new mapChooseWindow(this);
<<<<<<< HEAD
    gameplay_window = new gameplayWindow(this);
=======
    pause_menu = new PauseMenu(this);
>>>>>>> pause_menu
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

void Game::startGameplay() {
    if (map_choose_window->getMapBack() == map_choose_window->getMapsForChoose()[0]) {
        gameplay_window->setMap(gameplay_window->getMaps()[0]);
    } else if (map_choose_window->getMapBack() == map_choose_window->getMapsForChoose()[1]) {
        gameplay_window->setMap(gameplay_window->getMaps()[1]);
    }
    gameplay_window->showFullScreen();
    map_choose_window->close();
}

Game::~Game() {
    delete main_menu;
    delete map_choose_window;
    delete gameplay_window;
}
