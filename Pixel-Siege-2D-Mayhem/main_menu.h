#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QMainWindow>
#include <QMovie>
#include <QPaintEvent>
#include <QPushButton>
#include <QSpacerItem>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void exitSlot();

private:
    Ui::Game *ui;
    QMovie *background = new QMovie(":/backgrounds/background menu/back6.gif");
    QWidget* centralWidget;
    QSpacerItem* leftSpacer;
    QSpacerItem* rightSpacer;
    QPushButton* startButton;
    QPushButton* statsButton;
    QPushButton* achievementsButton;
    QPushButton* exitButton;
    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;
};
#endif // MAIN_MENU_H
