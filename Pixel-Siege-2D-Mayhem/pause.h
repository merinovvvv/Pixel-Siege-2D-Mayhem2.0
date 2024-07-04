#ifndef PAUSE_H
#define PAUSE_H

#include <QMainWindow>
#include <QMovie>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>

class Game;

class PauseMenu : public QMainWindow {
    Q_OBJECT
public:
    PauseMenu(Game* game, QWidget *parent = nullptr);
    ~PauseMenu() = default;

private slots:
    void exit();
    void back(); // this is continue but continue is a command so it's called back

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QMovie* background = new QMovie(":/backgrounds/background_menu/back8.gif");
    QPushButton* continue_button;
    QPushButton* exit_button;
    QVBoxLayout* buttonsLayout;
    QSpacerItem* topSpacer;
    QSpacerItem* bottomSpacer;
    QWidget* centralWidget;

    //void resetTheTime();

    Game* game_;
};

#endif // PAUSE_H
