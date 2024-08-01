#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QMovie>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

#include "main_menu.h"
#include "game.h"

MainMenu::MainMenu(Game* game, QWidget *parent) : QMainWindow(parent), game_(game) {
    setMouseTracking(true);
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    //showFullScreen();
    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);

    leftSpacer = new QSpacerItem(100, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    gridLayout->addItem(leftSpacer, 1, 0, 1, 1, Qt::AlignLeft);

    verticalLayout = new QVBoxLayout();
    verticalLayout->addSpacing(15);

    startButton = new QPushButton("PLAY");
    startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(startButton, &QPushButton::clicked, this, &MainMenu::showMapChooseWindow);

    statsButton = new QPushButton("STATS");
    statsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    exitButton = new QPushButton("EXIT");
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::exitSlot);

    QString styleSheet = ("QPushButton {"
                          "background: transparent;"
                          "color: white;"
                          "font-size: 110px;"
                          "border: none;"
                          "}"
                          "QPushButton:hover {"
                          "background: transparent;"
                          "color: rgb(255, 173, 30);"
                          "font-size: 110px;"
                          "border: none;"
                          "}"
                          "QPushButton:focus {"
                          "color: rgb(255, 173, 30);"
                          "border: none;"
                          "outline: none;"
                          "}");

    startButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);
    effect1->setColor(Qt::black);
    effect1->setOffset(4, 4);
    startButton->setGraphicsEffect(effect1);

    statsButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(10);
    effect2->setColor(Qt::black);
    effect2->setOffset(4, 4);
    statsButton->setGraphicsEffect(effect2);

    exitButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect;
    effect3->setBlurRadius(10);
    effect3->setColor(Qt::black);
    effect3->setOffset(4, 4);
    exitButton->setGraphicsEffect(effect3);

    verticalLayout->addWidget(startButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(statsButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    gridLayout->addLayout(verticalLayout, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignCenter);

    startButton->installEventFilter(this);
    statsButton->installEventFilter(this);
    exitButton->installEventFilter(this);
}

void MainMenu::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

void MainMenu::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == startButton) {
                showMapChooseWindow();
            } else if (focusedButton == exitButton) {
                exitSlot();
            }
        }
    } else {
        QMainWindow::keyPressEvent(event);
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

bool MainMenu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        startButton->clearFocus();
        statsButton->clearFocus();
        exitButton->clearFocus();

        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}
