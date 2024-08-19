#include <QApplication>
#include <QFontDatabase>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/ARCADECLASSIC.TTF");
    Game new_game;
    new_game.startApplication();
    return a.exec();
}
