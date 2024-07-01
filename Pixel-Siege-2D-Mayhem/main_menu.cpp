#include <QMovie>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

#include "main_menu.h"
#include "ui_main_menu.h"
#include "game.h"

MainMenu::MainMenu(Game* game, QWidget *parent) : QMainWindow(parent), ui(new Ui::Game), game_(game) {
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    showFullScreen();
    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    gridLayout = new QGridLayout(this);
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    leftSpacer = new QSpacerItem(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);
    //rightSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addItem(leftSpacer, 1, 1, 1, 1, Qt::AlignLeft);
    //gridLayout->addItem(rightSpacer, 1, 3, 1, 1, Qt::AlignRight);

    verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->addSpacing(15);

    startButton = new QPushButton("PLAY");
    startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect (startButton, SIGNAL(clicked()), this, SLOT(showMapChooseWindow()));

    statsButton = new QPushButton("STATS");
    statsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    achievementsButton = new QPushButton("ACHIEVEMNTS");
    achievementsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    exitButton = new QPushButton("EXIT");
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));

    QString styleSheet = "QPushButton {"
                         "background: transparent;"
                         "color: white;"
                         "font-size: 110px;"
                         "}"
                         "QPushButton:hover {"
                         "background: transparent;"
                         "color: rgb(255, 173, 30);"
                         "font-size: 110px;"
                         "}";

    startButton->setStyleSheet(styleSheet);
    statsButton->setStyleSheet(styleSheet);
    achievementsButton->setStyleSheet(styleSheet);
    exitButton->setStyleSheet(styleSheet);

    verticalLayout->addWidget(startButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(statsButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(achievementsButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    gridLayout->addItem(verticalLayout, 1, 2, 1, 1, Qt::AlignLeft | Qt::AlignCenter);
    setLayout(gridLayout);
}

void MainMenu::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

void MainMenu::exitSlot() {
    QApplication::quit();
}

void MainMenu::showMapChooseWindow() {
    if(game_) {
        game_->showMapChooseWindow();
    }
    this->close();
}

MainMenu::~MainMenu()
{
    delete ui;
    delete background;
}
