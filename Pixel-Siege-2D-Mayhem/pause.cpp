#include "pause.h"
#include "game.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>

PauseMenu::PauseMenu(Game* game, QWidget *parent) : QMainWindow(parent), game_(game) {
    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    // Создаем центральный виджет и устанавливаем макет для него
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //layout = new QGridLayout(centralWidget);
    //centralWidget->setLayout(layout);

    //rightSpacer = new QSpacerItem(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);
    //layout->addItem(rightSpacer, 2, 1, 1, 1, Qt::AlignRight);

    buttonsLayout = new QVBoxLayout();
    centralWidget->setLayout(buttonsLayout);

    continue_button = new QPushButton("CONTINUE");
    continue_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    exit_button = new QPushButton("BACK");
    exit_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString styleSheet = "QPushButton {"
                         "background: transparent;"
                         "color: #DADADA;"
                         "font-size: 110px;"
                         "text-align: center;"
                         "}"
                         "QPushButton:hover {"
                         "background: transparent;"
                         "color: rgb(255, 173, 30);"
                         "font-size: 110px;"
                         "text-align: center;"
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

//    layout->addLayout(buttonsLayout, 1, 1, 1, 1, Qt::AlignLeft);

    connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));
}


void PauseMenu::exit() {
    if(game_) {
        game_->showMainMenu();
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
