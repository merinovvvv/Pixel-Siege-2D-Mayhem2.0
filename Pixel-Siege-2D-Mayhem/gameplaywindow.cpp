#include <QKeyEvent>
#include <QTimer>

#include "gameplaywindow.h"
#include "mapchoosewindow.h"
#include "game.h"

gameplayWindow::gameplayWindow(Game* game, QWidget *parent)
    : QMainWindow{parent}, game_(game), view_(new QGraphicsView(this)), scene_(new QGraphicsScene(this)), character_(nullptr)
{
    this->setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));

    view_->setScene(scene_);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view_);
}

gameplayWindow::~gameplayWindow() {
    delete game_;
    delete scene_;
    delete view_;
    delete character_;
}

void gameplayWindow::setMap(QString& map) {
    map_ = map;
    scene_->setBackgroundBrush(QPixmap(map_));

    if (!character_) {
        character_ = new QGraphicsPixmapItem(QPixmap(":/character/mobs/knight1.png"));
        character_->setPos(100, 100);
        scene_->addItem(character_);
    }
}

QVector <QString> gameplayWindow::getMaps() {
    return maps_;
}

void gameplayWindow::keyPressEvent(QKeyEvent* event) {
    if (!character_) return;

    pressedKeys_.insert(event->key());

    switch (event->key()) {
    case Qt::Key_A:
        if (pressedKeys_.find(Qt::Key_S) != pressedKeys_.end()) {
            character_->moveBy(-10, 10);
            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else if (pressedKeys_.find(Qt::Key_W) != pressedKeys_.end()) {
            character_->moveBy(-10, -10);
            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else {
            character_->moveBy(-10, 0);
            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        }
        break;
    case Qt::Key_D:
        if (pressedKeys_.find(Qt::Key_S) != pressedKeys_.end()) {
            character_->moveBy(10, 10);
            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }
        } else if (pressedKeys_.find(Qt::Key_W) != pressedKeys_.end()) {
            character_->moveBy(10, -10);
            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }
        } else {
            character_->moveBy(10, 0);
            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }
        }
        break;
    case Qt::Key_W:
        if (pressedKeys_.find(Qt::Key_A) != pressedKeys_.end()) {
            character_->moveBy(-10, -10);
            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else if (pressedKeys_.find(Qt::Key_D) != pressedKeys_.end()) {
            character_->moveBy(10, -10);
            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }
        } else {
            character_->moveBy(0, -10);
        }
        break;
    case Qt::Key_S:
        if (pressedKeys_.find(Qt::Key_A) != pressedKeys_.end()) {
            character_->moveBy(-10, 10);
            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else if (pressedKeys_.find(Qt::Key_D) != pressedKeys_.end()) {
            character_->moveBy(10, 10);
            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }
        } else {
            character_->moveBy(0, 10);
        }
        break;
    case Qt::Key_Escape:
        game_->showPauseMenu();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void gameplayWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!character_) return;

    pressedKeys_.remove(event->key());
}
