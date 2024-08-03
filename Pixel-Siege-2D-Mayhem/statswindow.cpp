#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>

#include "statswindow.h"
#include "game.h"

statsWindow::statsWindow(Game* game, QWidget *parent) : QMainWindow(parent), game_(game)
{
    setMouseTracking(true);
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    //showFullScreen();
    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    backButton = new QPushButton();
    backButton->setText("BACK");

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
                          );

    backButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect1->setColor(Qt::black);
    effect1->setOffset(4, 4);  // Увеличение смещения для большей толщины
    backButton->setGraphicsEffect(effect1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(backButton);
    layout->addStretch();

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    backButton->installEventFilter(this);
}

void statsWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

void statsWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == backButton) {
                backSlot();
            }
        }
    } else if (event->key() == Qt::Key_Escape) {
        backSlot();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void statsWindow::backSlot() {
    if(game_) {
        game_->showMainMenu();
    }
    this->close();
}

bool statsWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        backButton->clearFocus();

        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}
