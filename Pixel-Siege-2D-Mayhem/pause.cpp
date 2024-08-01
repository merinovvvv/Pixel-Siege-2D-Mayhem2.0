#include "pause.h"
#include "game.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QTimer>

PauseMenu::PauseMenu(Game* game, QWidget *parent) : QMainWindow(parent), game_(game) {
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));

    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    // Создаем центральный виджет и устанавливаем макет для него
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    buttonsLayout = new QVBoxLayout();
    centralWidget->setLayout(buttonsLayout);

    continue_button = new QPushButton("CONTINUE");
    continue_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    exit_button = new QPushButton("EXIT");
    exit_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString styleSheet = "QPushButton {"
                         "background: transparent;"
                         "color: white;"
                         "font-size: 110px;"
                         "text-align: center;"
                         "border: none;"
                         "}"
                         "QPushButton:hover {"
                         "background: transparent;"
                         "color: #FF6439;"
                         "font-size: 110px;"
                         "text-align: center;"
                         "border: none;"
                         "}"
                         "QPushButton:focus{"
                         "color: #FF6439;"
                         "border: none;"
                         "outline: none;"
                         "}";

    continue_button->setStyleSheet(styleSheet);
    exit_button->setStyleSheet(styleSheet);

    // Добавление эффекта тени для имитации обводки
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect->setColor(Qt::black);
    effect->setOffset(4, 4);  // Увеличение смещения для большей толщины

    continue_button->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect2->setColor(Qt::black);
    effect2->setOffset(4, 4);  // Увеличение смещения для большей толщины

    exit_button->setGraphicsEffect(effect2);

    topSpacer = new QSpacerItem(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);
    bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);

    buttonsLayout->addItem(topSpacer);
    buttonsLayout->addWidget(continue_button, 0, Qt::AlignCenter);
    buttonsLayout->addWidget(exit_button, 0, Qt::AlignCenter);
    buttonsLayout->addItem(bottomSpacer);

    connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));
    connect(continue_button, SIGNAL(clicked()), this, SLOT(back()));
}

void PauseMenu::exit() {
    if(game_) {
        delete game_->gameplay_window;
        game_->gameplay_window = nullptr;
        game_->hero_ = nullptr;
        game_->showMainMenu();
    }
    this->close();
}

void PauseMenu::back() {
    if (game_) {
        //game_->gameplay_window->gameTime_->start();
        game_->gameplay_window->resumeTimer();
        game_->startGameplay();
    }
    this->close();
}

void PauseMenu::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

bool PauseMenu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {

        continue_button->clearFocus();
        exit_button->clearFocus();


        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}

void PauseMenu::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == continue_button) {
                back();
            } else if (focusedButton == exit_button) {
                exit();
            }
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
