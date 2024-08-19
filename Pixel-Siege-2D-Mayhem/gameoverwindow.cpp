#include <QGraphicsDropShadowEffect>

#include "gameoverwindow.h"
#include "game.h"

gameOverWindow::gameOverWindow(Game* game, QWidget *parent) : QMainWindow(parent), game_(game)
{
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));

    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    // Создаем центральный виджет и устанавливаем макет для него
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    buttonsLayout = new QVBoxLayout();
    centralWidget->setLayout(buttonsLayout);

    gameOverLabel = new QLabel();
    gameOverLabel->setText("GAME OVER");
    gameOverLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    try_again_button = new QPushButton("TRY AGAIN");
    try_again_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    exit_button = new QPushButton("EXIT");
    exit_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString styleSheet = "QPushButton {"
                         "background: transparent;"
                         "color: white;"
                         "font-size: 110px;"
                         "text-align: center;"
                         "border: none;"
                         "font-family: 'ArcadeClassic';"
                         "}"
                         "QPushButton:hover {"
                         "background: transparent;"
                         "color: #FF6439;"
                         "font-size: 110px;"
                         "text-align: center;"
                         "border: none;"
                         "font-family: 'ArcadeClassic';"
                         "}"
                         "QPushButton:focus{"
                         "color: #FF6439;"
                         "border: none;"
                         "outline: none;"
                         "font-family: 'ArcadeClassic';"
                         "}"
                         "QLabel {"
                         "color: white;"
                         "font-size: 150px;"
                         "font-family: 'ArcadeClassic';"
                         "}";

    gameOverLabel->setStyleSheet(styleSheet);
    try_again_button->setStyleSheet(styleSheet);
    exit_button->setStyleSheet(styleSheet);

    // Добавление эффекта тени для имитации обводки
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect->setColor(Qt::black);
    effect->setOffset(4, 4);  // Увеличение смещения для большей толщины

    try_again_button->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect2->setColor(Qt::black);
    effect2->setOffset(4, 4);  // Увеличение смещения для большей толщины

    exit_button->setGraphicsEffect(effect2);

    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect;
    effect3->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect3->setColor(Qt::black);
    effect3->setOffset(4, 4);  // Увеличение смещения для большей толщины

    gameOverLabel->setGraphicsEffect(effect3);


    topSpacer = new QSpacerItem(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);
    bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);

    buttonsLayout->addItem(topSpacer);
    buttonsLayout->addWidget(gameOverLabel, 0, Qt::AlignCenter);
    buttonsLayout->addItem(topSpacer);
    buttonsLayout->addWidget(try_again_button, 0, Qt::AlignCenter);
    buttonsLayout->addWidget(exit_button, 0, Qt::AlignCenter);
    buttonsLayout->addItem(bottomSpacer);
    buttonsLayout->addItem(bottomSpacer);

    connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));
    connect(try_again_button, SIGNAL(clicked()), this, SLOT(tryAgain()));
}

void gameOverWindow::exit() {
    if(game_) {
        delete game_->gameplay_window;
        game_->gameplay_window = nullptr;
        game_->hero_ = nullptr;
        game_->monsters_.clear();
        game_->startApplication();
    }
    this->close();
}

void gameOverWindow::tryAgain() {
    if (game_) {
        //game_->gameplay_window->gameTime_->start();
        game_->showMapChooseWindow();
    }
    this->close();
}

void gameOverWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

bool gameOverWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {

        try_again_button->clearFocus();
        exit_button->clearFocus();


        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}

void gameOverWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == try_again_button) {
                tryAgain();
            } else if (focusedButton == exit_button) {
                exit();
            }
        }
    } else if (event->key() == Qt::Key_Escape) {
        tryAgain();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
