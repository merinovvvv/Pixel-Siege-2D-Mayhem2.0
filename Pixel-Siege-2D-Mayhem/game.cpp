#include "game.h"

Game::Game() {
    login_window = new loginWindow(this);
    autho = new AuthoWindow(this);
    main_menu = new MainMenu(this);
    map_choose_window = new mapChooseWindow(this);
    pause_menu = new PauseMenu(this);
    gameplay_window = nullptr;
    hero_ = nullptr;
}

void Game::showLoginWindow() {
    login_window->showFullScreen();
}

void Game::startApplication() {
    autho->showFullScreen();
}

void Game::showMainMenu() {
    autho->close();
    login_window->close();
    main_menu->showFullScreen();
}

void Game::showMapChooseWindow() {
    map_choose_window->showFullScreen();
    main_menu->close();
}

void Game::showPauseMenu() {
    pause_menu->showFullScreen();
    gameplay_window->hide();
}

void Game::backToMainMenu() {
    main_menu->show();
    map_choose_window->close();
}

void Game::startGameplay() {

    if (gameplay_window == nullptr) {
        gameplay_window = new gameplayWindow(this);
    }

    if (map_choose_window->getMapBack().toImage() == map_choose_window->getMapsForChoose()[0].toImage()) {
        gameplay_window->setMap(gameplay_window->getMaps()[0]);
    } else if (map_choose_window->getMapBack().toImage() == map_choose_window->getMapsForChoose()[1].toImage()) {
        gameplay_window->setMap(gameplay_window->getMaps()[1]);
    }
    gameplay_window->showFullScreen();
    map_choose_window->close();
}

