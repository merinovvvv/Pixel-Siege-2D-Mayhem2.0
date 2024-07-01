#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game new_game;
    new_game.showPauseMenu();
    return a.exec();
}
