#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QSpacerItem>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>


class Game;

class loginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit loginWindow(Game* game, QWidget *parent = nullptr);
    ~loginWindow() = default;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void exitSlot();
    void authorizationSlot();
    void backSlot();

private:
    QMovie *background = new QMovie(":/backgrounds/background_menu/back6.gif");
    QWidget* centralWidget;
    QSpacerItem* leftSpacer;
    QLabel* loginLabel;
    QLineEdit* loginLineEdit;
    QLabel* passwordLabel;
    QLineEdit* passwordLineEdit;
    QPushButton* authoButton;
    QPushButton* exitButton;
    QPushButton* backButton;
    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;

    Game* game_;

    void authorization();
    bool playerExists();


signals:
};

#endif // LOGINWINDOW_H
