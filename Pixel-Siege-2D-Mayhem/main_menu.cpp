#include <QMovie>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

#include "main_menu.h"
#include "ui_main_menu.h"
#include "mapchoosewindow.h"

MainMenu::MainMenu(QWidget *parent) : QMainWindow(parent), ui(new Ui::Game) {
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

MainMenu::~MainMenu()
{
    delete ui;
    delete background;
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
    mapChooseWindow* w = new mapChooseWindow();

    QPropertyAnimation* animationShow = new QPropertyAnimation(w, "windowOpacity");
    animationShow->setDuration(200);
    animationShow->setStartValue(0.0);
    animationShow->setEndValue(1.0);

    //animation for smooth closing current window
    QPropertyAnimation* animationHide = new QPropertyAnimation(this, "windowOpacity");
    animationHide->setDuration(200);
    animationHide->setStartValue(1.0);
    animationHide->setEndValue(0.0);

    // show new window and start it's animation before closing current one
    w->showFullScreen();
    animationShow->start();

    // connect the signal of finishing an animation of opening new window before animation of closing current one
    connect(animationShow, &QPropertyAnimation::finished, this, [this, animationHide]() {
        animationHide->start();
    });

    connect(animationHide, &QPropertyAnimation::finished, this, &QWidget::close);
}

