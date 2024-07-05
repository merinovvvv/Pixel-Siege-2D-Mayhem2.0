#include "game.h"

Game::Game() {
    main_menu = new MainMenu(this);
    map_choose_window = new mapChooseWindow(this);
    //gameplay_window = new gameplayWindow(this);
    pause_menu = new PauseMenu(this);
    gameplay_window = nullptr;
    hero_ = nullptr;
}

void Game::showMainMenu() {
    main_menu->show();
    // map_choose_window->close();
    // pause_menu->close();
    // gameplay_window->close();
}

void Game::showMapChooseWindow() {
    map_choose_window->showFullScreen();
    main_menu->close();
    // pause_menu->close();
    // gameplay_window->close();
}

void Game::showPauseMenu() {
    pause_menu->showFullScreen();
    gameplay_window->hide();
    // main_menu->close();
    // map_choose_window->close();
    // main_menu->close();
    // map_choose_window->close();
    // gameplay_window->hide();
}

void Game::backToMainMenu() {
    main_menu->show();
    map_choose_window->close();
}

void Game::startGameplay() {

    if (gameplay_window == nullptr) {
        gameplay_window = new gameplayWindow(this);
    }

    if (map_choose_window->getMapBack() == map_choose_window->getMapsForChoose()[0]) {
        gameplay_window->setMap(gameplay_window->getMaps()[0]);
    } else if (map_choose_window->getMapBack() == map_choose_window->getMapsForChoose()[1]) {
        gameplay_window->setMap(gameplay_window->getMaps()[1]);
    }
    gameplay_window->showFullScreen();
    map_choose_window->close();
}

