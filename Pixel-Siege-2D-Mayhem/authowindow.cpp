#include "authowindow.h"
#include "game.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QApplication>

int AuthoWindow::senderButton = -1;

AuthoWindow::AuthoWindow(Game* game, QWidget *parent) : QMainWindow(parent), game_(game)
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

    signIn = new QPushButton("SIGN IN");
    signIn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(signIn, SIGNAL(clicked()), this, SLOT(showLoginWindow()));

    signUp = new QPushButton("SIGN UP");
    signUp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(signIn, SIGNAL(clicked()), this, SLOT(showLoginWindow()));

    exitButton = new QPushButton("EXIT");
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));

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
                          "QPushButton:focus{"
                          "color: rgb(255, 173, 30);"
                          "border: none;"
                          "outline: none;"
                          "}");

    signIn->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect1->setColor(Qt::black);
    effect1->setOffset(4, 4);  // Увеличение смещения для большей толщины
    signIn->setGraphicsEffect(effect1);

    signUp->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect2->setColor(Qt::black);
    effect2->setOffset(4, 4);  // Увеличение смещения для большей толщины
    signUp->setGraphicsEffect(effect2);

    exitButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect;
    effect4->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect4->setColor(Qt::black);
    effect4->setOffset(4, 4);  // Увеличение смещения для большей толщины
    exitButton->setGraphicsEffect(effect4);

    verticalLayout->addWidget(signIn, 0, Qt::AlignCenter);
    verticalLayout->addWidget(signUp, 0, Qt::AlignCenter);
    verticalLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    // Добавляем verticalLayout в сетку
    QWidget* buttonsWidget = new QWidget(this);
    buttonsWidget->setLayout(verticalLayout);
    gridLayout->addWidget(buttonsWidget, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignCenter);
    centralWidget->setLayout(gridLayout);

    signIn->installEventFilter(this);
    signUp->installEventFilter(this);
    exitButton->installEventFilter(this);
}

void AuthoWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

void AuthoWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == signIn || focusedButton == signUp) {
                showLoginWindow();
            } else if (focusedButton == exitButton) {
                exitSlot();
            }
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void AuthoWindow::exitSlot() {
    QApplication::quit();
}

bool AuthoWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        signIn->clearFocus();
        signUp->clearFocus();
        exitButton->clearFocus();

        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}

void AuthoWindow::showLoginWindow() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button == signIn) {
        senderButton = 0;
    } else if (button == signUp) {
        senderButton = 1;
    }
    if(game_) {
        game_->showLoginWindow();
    }
    this->close();
}
