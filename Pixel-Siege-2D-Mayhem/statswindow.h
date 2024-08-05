#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QJsonArray>

class Game;

class statsWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit statsWindow(Game* game, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void backSlot();

private:
    QMovie *background = new QMovie(":/backgrounds/background_menu/back1.gif");
    QWidget* centralWidget;
    QPushButton* backButton;
    QTableWidget* tableWidget;
    QWidget* tableContainer;
    QVBoxLayout* tableLayout;
    QJsonArray playersArray;

    void loadJsonData();
    void populateTable();

    Game* game_;

signals:
};

#endif // STATSWINDOW_H
