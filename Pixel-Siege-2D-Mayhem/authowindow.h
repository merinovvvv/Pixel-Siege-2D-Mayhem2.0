#ifndef AUTHOWINDOW_H
#define AUTHOWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QSpacerItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPaintEvent>

class Game;

class AuthoWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AuthoWindow(Game* game, QWidget *parent = nullptr);
    ~AuthoWindow() = default;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void exitSlot();
    void showLoginWindow();

private:
    QMovie *background = new QMovie(":/backgrounds/background_menu/back6.gif");
    QWidget* centralWidget;
    QSpacerItem* leftSpacer;
    QPushButton* signIn;
    QPushButton* signUp;
    QPushButton* exitButton;
    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;

    Game* game_;

signals:
};

#endif // AUTHOWINDOW_H
