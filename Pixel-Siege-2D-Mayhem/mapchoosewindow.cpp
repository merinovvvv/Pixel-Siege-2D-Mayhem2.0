#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QScreen>
#include <QSpacerItem>
#include <QPropertyAnimation>
#include <QTimer>

#include "mapchoosewindow.h"
#include "main_menu.h"
#include "game.h"

mapChooseWindow::mapChooseWindow(Game* game, QWidget *parent)
    : QMainWindow{parent}, game_(game)
{

    mapChooseBackground = new QMovie(":/backgrounds/background_menu/back5.gif");
    connect(mapChooseBackground, &QMovie::frameChanged, this, [this]() {
        this->update();
    });
    mapChooseBackground->start();

    this->setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));

    backButton = new QPushButton();
    backButton->setText("BACK");
    backButton->setStyleSheet("QPushButton {"
                              "    background-color: transparent;"
                              "    border: none;"
                              "    color: white;"
                              "    font-size: 40pt;"
                              "}"
                              "QPushButton:hover {"
                              "    color: rgb(255, 173, 30);"
                              "}");


    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *chooseMapLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(chooseMapLayout);

    chooseMapLayout->addWidget(backButton, 0, Qt::AlignTop | Qt::AlignLeft);


    chooseMap = new QLabel();
    chooseMap->setText("CHOOSE A MAP");
    chooseMap->setStyleSheet("background-color: transparent; border: none; color: white; font-size: 40pt;");

    chooseMap->setAlignment(Qt::AlignCenter);
    chooseMapLayout->addWidget(chooseMap, 0, Qt::AlignCenter);

    QSpacerItem* middleSpacer_1 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    chooseMapLayout->addItem(middleSpacer_1);

    QHBoxLayout* MapsAndArrows = new QHBoxLayout(centralWidget);
    centralWidget->setLayout(MapsAndArrows);

    leftButton = new QPushButton("<", this);

    leftButton->setStyleSheet("QPushButton {"
                              "    background-color: transparent;"
                              "    border: none;"
                              "    color: white;"
                              "    font-size: 40pt;"
                              "}"
                              "QPushButton:hover {"
                              "    color: rgb(255, 173, 30);"
                              "}");

    MapsAndArrows->addWidget(leftButton);

    rightButton = new QPushButton(">", this);

    rightButton->setStyleSheet("QPushButton {"
                              "    background-color: transparent;"
                              "    border: none;"
                              "    color: white;"
                              "    font-size: 40pt;"
                              "}"
                              "QPushButton:hover {"
                              "    color: rgb(255, 173, 30);"
                              "}");

    mapChooseScene = new QGraphicsScene(this);
    mapChooseView = new QGraphicsView(mapChooseScene, this);

    mapsForChoose.append(QPixmap(":/backgrounds/background_gameplay/grassForChoose.png"));
    mapsForChoose.append(QPixmap(":/backgrounds/background_gameplay/sandForChoose.jpg"));

    mapBack = mapsForChoose[0];
    mapItem = new QGraphicsRectItem(0, 0, mapBack.width(), mapBack.height());
    mapItem->setBrush(QBrush(mapBack));

    mapChooseView->setFixedSize(mapBack.width() + 10, mapBack.height() + 10);

    mapChooseScene->addItem(mapItem);

    mapChooseView->show();

    MapsAndArrows->addWidget(mapChooseView);
    MapsAndArrows->addWidget(rightButton);
    chooseMapLayout->addLayout(MapsAndArrows);

    QSpacerItem* middleSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    chooseMapLayout->addItem(middleSpacer_2);

    startButton = new QPushButton();
    startButton->setText("START");
    startButton->setStyleSheet("QPushButton {"
                              "    background-color: transparent;"
                              "    border: none;"
                              "    color: white;"
                              "    font-size: 40pt;"
                              "}"
                              "QPushButton:hover {"
                              "    color: rgb(255, 173, 30);"
                              "}");

    chooseMapLayout->addWidget(startButton);

    QSpacerItem* lowerSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    chooseMapLayout->addItem(lowerSpacer);

    connect(leftButton, SIGNAL(clicked()), this, SLOT(changeMap()));
    connect(rightButton, SIGNAL(clicked()), this, SLOT(changeMap()));

    connect(backButton, SIGNAL(clicked()), this, SLOT(backToMainMenu()));
    // connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
}

void mapChooseWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (mapChooseBackground && mapChooseBackground->isValid()) {
        QPixmap pixmap = mapChooseBackground->currentPixmap();
        painter.drawPixmap(0, 0, width(), height(), pixmap);
    }

    QMainWindow::paintEvent(event);
}

// void mapChooseWindow::showMapChooseWindow(mapChooseWindow* window) {
//     if (window) {
//         window->showFullScreen();
//     }
// }

void mapChooseWindow::changeMap() {

    QPushButton *buttonClicked = qobject_cast<QPushButton *>(sender());
    if (buttonClicked == leftButton) {
        currentIndex = (currentIndex - 1 + mapsForChoose.size()) % mapsForChoose.size();
    } else if (buttonClicked == rightButton) {
        currentIndex = (currentIndex + 1) % mapsForChoose.size();
    }

    mapBack = mapsForChoose[currentIndex];
    mapItem->setRect(0, 0, mapBack.width(), mapBack.height());
    mapItem->setBrush(QBrush(mapBack));


    mapChooseScene->update();
}

void mapChooseWindow::backToMainMenu() {
    if(game_) {
        game_->backToMainMenu();
    }
    this->close();
}

mapChooseWindow::~mapChooseWindow() {
    delete mapChooseBackground;
}
