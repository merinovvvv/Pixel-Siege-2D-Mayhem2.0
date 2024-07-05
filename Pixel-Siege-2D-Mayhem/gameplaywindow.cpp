#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QtMath>

#include "gameplaywindow.h"
#include "mapchoosewindow.h"
#include "game.h"

gameplayWindow::gameplayWindow(Game* game, QWidget *parent)
    : QMainWindow{parent}, game_(game), view_(new QGraphicsView(this)), scene_(new QGraphicsScene(this)), character_(nullptr)
{
    this->setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));

    hpLabel_ = new QLabel();
    hpLabel_->setText("HP");

    healthBar_ = new QProgressBar();
    healthBar_->setRange(0, 100);
    healthBar_->setValue(100);
    //healthBar_->setFixedSize(200, 20);
    //healthBar_->show();

    QHBoxLayout* hpLayout = new QHBoxLayout();
    hpLayout->addWidget(hpLabel_);
    hpLayout->addWidget(healthBar_);

    QWidget* hpWidget = new QWidget();
    hpWidget->setLayout(hpLayout);

    QWidget* containerWidget = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->addWidget(hpWidget);
    containerLayout->addWidget(view_);
    containerLayout->setContentsMargins(0, 10, 0, 0); // Задает отступы от краев контейнера

    setCentralWidget(containerWidget);


    // QGraphicsProxyWidget* proxy = scene_->addWidget(healthBar_);
    // proxy->setPos(10, 10); // Устанавливаем позицию на сцене

    view_->setScene(scene_);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setCentralWidget(view_);
}

void gameplayWindow::setMap(QString& map) {
    map_ = map;
    QPixmap scaledMap = QPixmap(map_).scaled(1920, 1080, Qt::IgnoreAspectRatio);
    background_ = new QGraphicsPixmapItem(scaledMap);
    background_->setZValue(0);
    scene_->addItem(background_);

    if (!character_) {
        character_ = new QGraphicsPixmapItem(QPixmap(":/character/mobs/knight1_sword1.png"));
        character_->setZValue(1);
        qreal x = character_->boundingRect().width() / 2;
        qreal y = character_->boundingRect().height() / 2;
        character_->setPos(scene_->sceneRect().center() + QPointF(-x, -y));
        scene_->addItem(character_);
    }
}

QVector <QString> gameplayWindow::getMaps() {
    return maps_;
}

void gameplayWindow::keyPressEvent(QKeyEvent* event) {
    if (!character_) return;

    pressedKeys_.insert(event->nativeScanCode());
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

    switch (event->nativeScanCode()) {
    case 30:
        if (pressedKeys_.find(31) != pressedKeys_.end()) {

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
                character_->moveBy(-5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else if (pressedKeys_.find(17) != pressedKeys_.end()) {

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
                character_->moveBy(-5 * qSqrt(2), -5 * qSqrt(2));
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
    case 32:
        if (pressedKeys_.find(31) != pressedKeys_.end()) {

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
                character_->moveBy(5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (facingLeft) {
                character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else if (pressedKeys_.find(17) != pressedKeys_.end()) {

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
                character_->moveBy(5 * qSqrt(2), -5 * qSqrt(2));
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
    case 17:
        if (pressedKeys_.find(30) != pressedKeys_.end()) {
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
                character_->moveBy(-5 * qSqrt(2), -5 * qSqrt(2));
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else if (pressedKeys_.find(32) != pressedKeys_.end()) {

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
                character_->moveBy(5 * qSqrt(2), -5 * qSqrt(2));
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
    case 31:
        if (pressedKeys_.find(30) != pressedKeys_.end()) {

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
                character_->moveBy(-5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (!facingLeft) {
                character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else if (pressedKeys_.find(32) != pressedKeys_.end()) {

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
                character_->moveBy(5 * qSqrt(2), 5 * qSqrt(2));
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
    case 1:
        game_->showPauseMenu();
        break;
    case 57: {
        Hit();
        break;
    }
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void gameplayWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Hit();
    }
}

void gameplayWindow::Hit() {
    QGraphicsPixmapItem* hitImage = new QGraphicsPixmapItem(hit);
    if (!facingLeft) {
        QTransform transform2;
        transform2.scale(0.1, 0.1);
        hitImage->setTransform(transform2);
        hitImage->setPos(character_->pos().x() + 82, character_->pos().y() + 28);
    } else {
        QTransform transform;
        transform.scale(-0.1, 0.1);
        hitImage->setTransform(transform);
        hitImage->setPos(character_->pos().x() + 88, character_->pos().y() + 28);
    }

    scene_->addItem(hitImage);

    QTimer::singleShot(100, [hitImage, this]() {
        scene_->removeItem(hitImage);
        delete hitImage;
    });
}

void gameplayWindow::updateHealth(int health) {
    healthBar_->setValue(health);
}

void gameplayWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!character_) return;

    pressedKeys_.remove(event->nativeScanCode());
}
