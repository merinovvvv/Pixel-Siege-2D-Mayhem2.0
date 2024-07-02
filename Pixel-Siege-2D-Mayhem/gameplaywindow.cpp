#include <QApplication>
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
    scene_->addPixmap(QPixmap(map_));

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
    QRectF characterRect = character_->boundingRect();
    qreal characterLeft = characterRect.left() + character_->x();
    qreal characterRight = characterRect.right() + character_->x();
    qreal characterTop = characterRect.top() + character_->y();
    qreal characterBottom = characterRect.bottom() + character_->y();

    mapBorder_ = scene_->sceneRect();
    qreal mapLeft = mapBorder_.left();
    qreal mapRight = mapBorder_.right();
    qreal mapTop = mapBorder_.top();
    qreal mapBottom = mapBorder_.bottom();

    switch (event->key()) {
    case Qt::Key_A:
        if (pressedKeys_.find(Qt::Key_S) != pressedKeys_.end()) {

            // Когда мы упёрлись в левую границу и упёрлись в нижнюю
            if (characterLeft <= mapLeft && characterBottom >= mapBottom) {
                character_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в нижнюю
            } else if (characterLeft <= mapLeft && characterBottom < mapBottom) {
                character_->moveBy(0, 10);
                // Когда не упёрлись в левую границу и упёрлись в нижнюю
            } else if (characterLeft > mapLeft && characterBottom >= mapBottom) {
                character_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterBottom < mapBottom) {
                character_->moveBy(-10, 10);
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else if (pressedKeys_.find(Qt::Key_W) != pressedKeys_.end()) {

            // Когда мы упёрлись в левую границу и упёрлись в верхнюю
            if (characterLeft <= mapLeft && characterTop <= mapTop) {
                character_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в верхнюю
            } else if (characterLeft <= mapLeft && characterTop > mapTop) {
                character_->moveBy(0, -10);
                // Когда не упёрлись в левую границу и упёрлись в верхнюю
            } else if (characterLeft > mapLeft && characterTop <= mapTop) {
                character_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterTop > mapTop) {
                character_->moveBy(-10, -10);
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else {

            if(characterLeft <= mapLeft) {
                character_->moveBy(0, 0);
            } else {
                character_->moveBy(-10, 0);
            }
            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        }
        break;
    case Qt::Key_D:
        if (pressedKeys_.find(Qt::Key_S) != pressedKeys_.end()) {

            // Когда упёрлись в правую и нижнюю границы
            if (characterRight >= mapRight && characterBottom >= mapBottom) {
                character_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в нижнюю границы
            } else if (characterRight >= mapRight && characterBottom < mapBottom) {
                character_->moveBy(0, 10);
                // Когда не упрёлись в правую и упёрлись в нижнюю границу
            } else if (characterRight < mapRight && characterBottom >= mapBottom) {
                character_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterBottom < mapBottom) {
                character_->moveBy(10, 10);
            }

            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else if (pressedKeys_.find(Qt::Key_W) != pressedKeys_.end()) {

            // Когда упёрлись в правую и верхнюю границы
            if (characterRight >= mapRight && characterTop <= mapTop) {
                character_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в верхнюю границы
            } else if (characterRight >= mapRight && characterTop > mapTop) {
                character_->moveBy(0, -10);
                // Когда не упрёлись в правую и упёрлись в верхнюю границу
            } else if (characterRight < mapRight && characterTop <= mapTop) {
                character_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterTop > mapTop) {
                character_->moveBy(10, -10);
            }

            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else {

            if (characterRight >= mapRight) {
                character_->moveBy(0, 0);
            } else {
                character_->moveBy(10, 0);
            }
            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }
        }
        break;
    case Qt::Key_W:
        if (pressedKeys_.find(Qt::Key_A) != pressedKeys_.end()) {
            // Когда мы упёрлись в левую границу и упёрлись в верхнюю
            if (characterLeft <= mapLeft && characterTop <= mapTop) {
                character_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в верхнюю
            } else if (characterLeft <= mapLeft && characterTop > mapTop) {
                character_->moveBy(0, -10);
                // Когда не упёрлись в левую границу и упёрлись в верхнюю
            } else if (characterLeft > mapLeft && characterTop <= mapTop) {
                character_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterTop > mapTop) {
                character_->moveBy(-10, -10);
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else if (pressedKeys_.find(Qt::Key_D) != pressedKeys_.end()) {

            // Когда упёрлись в правую и верхнюю границы
            if (characterRight >= mapRight && characterTop <= mapTop) {
                character_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в верхнюю границы
            } else if (characterRight >= mapRight && characterTop > mapTop) {
                character_->moveBy(0, -10);
                // Когда не упрёлись в правую и упёрлись в верхнюю границу
            } else if (characterRight < mapRight && characterTop <= mapTop) {
                character_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterTop > mapTop) {
                character_->moveBy(10, -10);
            }

            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else {
            if (characterTop <= mapTop) {
                character_->moveBy(0, 0);
            } else {
                character_->moveBy(0, -10);
            }
        }
        break;
    case Qt::Key_S:
        if (pressedKeys_.find(Qt::Key_A) != pressedKeys_.end()) {

            // Когда мы упёрлись в левую границу и упёрлись в нижнюю
            if (characterLeft <= mapLeft && characterBottom >= mapBottom) {
                character_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в нижнюю
            } else if (characterLeft <= mapLeft && characterBottom < mapBottom) {
                character_->moveBy(0, 10);
                // Когда не упёрлись в левую границу и упёрлись в нижнюю
            } else if (characterLeft > mapLeft && characterBottom >= mapBottom) {
                character_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterBottom < mapBottom) {
                character_->moveBy(-10, 10);
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else if (pressedKeys_.find(Qt::Key_D) != pressedKeys_.end()) {

            // Когда упёрлись в правую и нижнюю границы
            if (characterRight >= mapRight && characterBottom >= mapBottom) {
                character_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в нижнюю границы
            } else if (characterRight >= mapRight && characterBottom < mapBottom) {
                character_->moveBy(0, 10);
                // Когда не упрёлись в правую и упёрлись в нижнюю границу
            } else if (characterRight < mapRight && characterBottom >= mapBottom) {
                character_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterBottom < mapBottom) {
                character_->moveBy(10, 10);
            }

            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else {
            if (characterBottom >= mapBottom) {
                character_->moveBy(0, 0);
            } else {
                character_->moveBy(0, 10);
            }
        }
        break;
    case Qt::Key_Escape:
        game_->showPauseMenu();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void gameplayWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!character_) return;

    pressedKeys_.remove(event->key());
}
