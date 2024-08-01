#include <QGraphicsDropShadowEffect>
#include <QPaintEvent>
#include <QApplication>

#include "loginwindow.h"
#include "game.h"

loginWindow::loginWindow(Game* game, QWidget *parent) : QMainWindow(parent), game_(game)
{
    setMouseTracking(true);
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    //showFullScreen();
    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);

    // Увеличиваем ширину leftSpacer
    leftSpacer = new QSpacerItem(100, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    gridLayout->addItem(leftSpacer, 0, 0, 1, 1);

    verticalLayout = new QVBoxLayout();
    verticalLayout->addSpacing(15);

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
                          "}"
                          "QLabel {"
                          "color: white;"
                          "font-size: 50px;"
                          "}"
                          "QLineEdit {"
                          "background: white;"
                          "color: black;"
                          "font-size: 50px;"
                          "border: 1px solid gray;"
                          "}"
                          "QLineEdit:focus {"
                          "background: rgb(255, 173, 30);"
                          "color: black;"
                          "}"
                          );


    QHBoxLayout* loginLayout = new QHBoxLayout();

    loginLabel = new QLabel("LOGIN");
    loginLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    loginLabel->setStyleSheet(styleSheet);

    loginLineEdit = new QLineEdit();
    loginLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    loginLineEdit->setStyleSheet(styleSheet);

    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginLineEdit);

    QHBoxLayout* passwordLayout = new QHBoxLayout();

    passwordLabel = new QLabel("PASSWORD");
    passwordLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    passwordLabel->setStyleSheet(styleSheet);

    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    passwordLineEdit->setStyleSheet(styleSheet);

    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);

    authoButton = new QPushButton("AUTHORIZE");
    authoButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(authoButton, SIGNAL(clicked()), this, SLOT(authorizationSlot()));
    //connect(authoButton, SIGNAL(clicked()), this, SLOT(showMainMenu()));

    exitButton = new QPushButton("EXIT");
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));

    authoButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect1->setColor(Qt::black);
    effect1->setOffset(4, 4);  // Увеличение смещения для большей толщины
    authoButton->setGraphicsEffect(effect1);

    exitButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect2->setColor(Qt::black);
    effect2->setOffset(4, 4);  // Увеличение смещения для большей толщины
    exitButton->setGraphicsEffect(effect2);

    verticalLayout->addLayout(loginLayout, 0);
    verticalLayout->addLayout(passwordLayout, 0);
    verticalLayout->addWidget(authoButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    // Добавляем verticalLayout в сетку
    QWidget* buttonsWidget = new QWidget(this);
    buttonsWidget->setLayout(verticalLayout);
    gridLayout->addWidget(buttonsWidget, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignCenter);
    centralWidget->setLayout(gridLayout);

    authoButton->installEventFilter(this);
    exitButton->installEventFilter(this);
}

void loginWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

void loginWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == authoButton) {
                authorizationSlot();
            } else if (focusedButton == exitButton) {
                exitSlot();
            }
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void loginWindow::exitSlot() {
    QApplication::quit();
}

bool loginWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        authoButton->clearFocus();
        exitButton->clearFocus();

        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}

void loginWindow::authorizationSlot() {
    if(game_) {
        game_->showMainMenu();
    }
    this->close();
}

