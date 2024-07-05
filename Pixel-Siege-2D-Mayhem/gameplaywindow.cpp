#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QtMath>
#include <QRandomGenerator>

#include "gameplaywindow.h"
#include "mapchoosewindow.h"
#include "game.h"
#include "hero.h"

gameplayWindow::gameplayWindow(Game* game, QWidget *parent)
    : QMainWindow{parent}, game_(game), view_(new QGraphicsView(this)), scene_(new QGraphicsScene(this))
{
    this->setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    setCursor(Qt::BlankCursor);

    showTime_ = new QLabel();
    //showTime_->setFixedSize(200, 10);
    showTime_->setStyleSheet("font-size: 35px;");
    showTime_->setText("00:00:00");
    startTime_ = QTime::currentTime();
    gameTime_ = new QTimer();
    connect(gameTime_, SIGNAL(timeout()), this, SLOT(updateTimer()));
    gameTime_->start(1000);
    //updateTimer();

    hpLabel_ = new QLabel();
    hpLabel_->setText("HP");
    hpLabel_->setStyleSheet("font-size: 35px;");

    healthBar_ = new QProgressBar();
    healthBar_->setRange(0, 100);
    healthBar_->setValue(100);
    healthBar_->setStyleSheet("QProgressBar::chunk {background-color: red;}");

    healthBar_->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid grey;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    color: white;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}");

    QSpacerItem* space = new QSpacerItem(1400, 0, QSizePolicy::Preferred, QSizePolicy::Fixed);

    QHBoxLayout* menuLayout = new QHBoxLayout();
    menuLayout->addWidget(showTime_);
    menuLayout->addItem(space);
    menuLayout->addWidget(hpLabel_);
    menuLayout->addWidget(healthBar_);

    QWidget* containerWidget = new QWidget();
    containerWidget->setFixedWidth(1900);
    containerWidget->setStyleSheet("background-color: transparent;");
    containerWidget->setLayout(menuLayout);
    containerWidget->setCursor(Qt::BlankCursor);

    QGraphicsProxyWidget *toShow = scene_->addWidget(containerWidget);
    toShow->setPos(10, 10);
    //toShow->setWindowFlags(Qt::FramelessWindowHint);
    toShow->setZValue(2);


    view_->setScene(scene_);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view_);

    ghost_ = Monster(10, 2, models_.ghost_, hit_);
    scaryGhost_ = Monster(20, 4, models_.scaryGhost_, hit_);
    skeleton_ = Monster(5, 1, models_.skeleton_, hit_);
    slime_ = Monster(10, 2, models_.slime_, hit_);
    wolf_ = Monster(25, 5, models_.wolf_, hit_);
}

void gameplayWindow::setMap(QString& map) {
    map_ = map;
    QPixmap scaledMap = QPixmap(map_).scaled(1920, 1080, Qt::IgnoreAspectRatio);
    background_ = new QGraphicsPixmapItem(scaledMap);
    background_->setZValue(0);
    scene_->addItem(background_);

<<<<<<< HEAD
    if (!character_) {
        character_ = new QGraphicsPixmapItem(QPixmap(":/character/mobs/knight1_sword1.png"));
        character_->setZValue(4);
        qreal x = character_->boundingRect().width() / 2;
        qreal y = character_->boundingRect().height() / 2;
        character_->setPos(scene_->sceneRect().center() + QPointF(-x, -y));
        scene_->addItem(character_);
=======
    if (game_->hero_ == nullptr) {
        game_->hero_ = new Hero(game_, this);
>>>>>>> 6e36df77ba3cc0bdc97ccc06ec6f0c2038e196e0
    }
}

QVector <QString> gameplayWindow::getMaps() {
    return maps_;
}

void gameplayWindow::spawnGhost() {
    Monster* monster = new Monster(ghost_);
    QGraphicsPixmapItem* model = new QGraphicsPixmapItem(monster->getModel()->pixmap());
    model->setZValue(2);
    model->setPos(QPointF(QRandomGenerator::global()->bounded(50, 1800), QRandomGenerator::global()->bounded(50, 900)));
    scene_->addItem(model);
    delete monster;
}

void gameplayWindow::keyPressEvent(QKeyEvent* event) {
    if (game_->hero_ == nullptr) return;

    pressedKeys_.insert(event->nativeScanCode());
    QRectF characterRect = game_->hero_->heroImage_->boundingRect();
    qreal characterLeft = characterRect.left() + game_->hero_->heroImage_->x();
    qreal characterRight = characterRect.right() + game_->hero_->heroImage_->x();
    qreal characterTop = characterRect.top() + game_->hero_->heroImage_->y();
    qreal characterBottom = characterRect.bottom() + game_->hero_->heroImage_->y();

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
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в нижнюю
            } else if (characterLeft <= mapLeft && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 10);
                // Когда не упёрлись в левую границу и упёрлись в нижнюю
            } else if (characterLeft > mapLeft && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (!facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else if (pressedKeys_.find(17) != pressedKeys_.end()) {

            // Когда мы упёрлись в левую границу и упёрлись в верхнюю
            if (characterLeft <= mapLeft && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в верхнюю
            } else if (characterLeft <= mapLeft && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(0, -10);
                // Когда не упёрлись в левую границу и упёрлись в верхнюю
            } else if (characterLeft > mapLeft && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), -5 * qSqrt(2));
            }

            if (!facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else {

            if(characterLeft <= mapLeft) {
                game_->hero_->heroImage_->moveBy(0, 0);
            } else {
                game_->hero_->heroImage_->moveBy(-10, 0);
            }
            if (!facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        }
        break;
    case 32:
        if (pressedKeys_.find(31) != pressedKeys_.end()) {

            // Когда упёрлись в правую и нижнюю границы
            if (characterRight >= mapRight && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в нижнюю границы
            } else if (characterRight >= mapRight && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 10);
                // Когда не упрёлись в правую и упёрлись в нижнюю границу
            } else if (characterRight < mapRight && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(-1, 0, 0, 1, game_->hero_->heroImage_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else if (pressedKeys_.find(17) != pressedKeys_.end()) {

            // Когда упёрлись в правую и верхнюю границы
            if (characterRight >= mapRight && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в верхнюю границы
            } else if (characterRight >= mapRight && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(0, -10);
                // Когда не упрёлись в правую и упёрлись в верхнюю границу
            } else if (characterRight < mapRight && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), -5 * qSqrt(2));
            }

            if (facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(-1, 0, 0, 1, game_->hero_->heroImage_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else {

            if (characterRight >= mapRight) {
                game_->hero_->heroImage_->moveBy(0, 0);
            } else {
                game_->hero_->heroImage_->moveBy(10, 0);
            }
            if (facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(-1, 0, 0, 1, game_->hero_->heroImage_->boundingRect().width(), 0));
                facingLeft = false;
            }
        }
        break;
    case 17:
        if (pressedKeys_.find(30) != pressedKeys_.end()) {
            // Когда мы упёрлись в левую границу и упёрлись в верхнюю
            if (characterLeft <= mapLeft && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в верхнюю
            } else if (characterLeft <= mapLeft && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(0, -10);
                // Когда не упёрлись в левую границу и упёрлись в верхнюю
            } else if (characterLeft > mapLeft && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), -5 * qSqrt(2));
            }

            if (!facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }
        } else if (pressedKeys_.find(32) != pressedKeys_.end()) {

            // Когда упёрлись в правую и верхнюю границы
            if (characterRight >= mapRight && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в верхнюю границы
            } else if (characterRight >= mapRight && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(0, -10);
                // Когда не упрёлись в правую и упёрлись в верхнюю границу
            } else if (characterRight < mapRight && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), -5 * qSqrt(2));
            }

            if (facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(-1, 0, 0, 1, game_->hero_->heroImage_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else {
            if (characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(0, 0);
            } else {
                game_->hero_->heroImage_->moveBy(0, -10);
            }
        }
        break;
    case 31:
        if (pressedKeys_.find(30) != pressedKeys_.end()) {

            // Когда мы упёрлись в левую границу и упёрлись в нижнюю
            if (characterLeft <= mapLeft && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда мы упёрлись в левую границу и не упёрлись в нижнюю
            } else if (characterLeft <= mapLeft && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 10);
                // Когда не упёрлись в левую границу и упёрлись в нижнюю
            } else if (characterLeft > mapLeft && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (!facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
                facingLeft = true;
            }

        } else if (pressedKeys_.find(32) != pressedKeys_.end()) {

            // Когда упёрлись в правую и нижнюю границы
            if (characterRight >= mapRight && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 0);
                // Когда упёрлись в правую и не упрёлись в нижнюю границы
            } else if (characterRight >= mapRight && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 10);
                // Когда не упрёлись в правую и упёрлись в нижнюю границу
            } else if (characterRight < mapRight && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), 5 * qSqrt(2));
            }

            if (facingLeft) {
                game_->hero_->heroImage_->setTransform(QTransform(-1, 0, 0, 1, game_->hero_->heroImage_->boundingRect().width(), 0));
                facingLeft = false;
            }

        } else {
            if (characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(0, 0);
            } else {
                game_->hero_->heroImage_->moveBy(0, 10);
            }
        }
        break;
    case 1:
        pauseTimer();
        //gameTime_->stop();
        game_->showPauseMenu();
        break;
    // case 57: {
    //     Hit();
    //     break;
    // }
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void gameplayWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Hit();
        spawnGhost();
    }
}

void gameplayWindow::Hit() {
    QGraphicsPixmapItem* hitImage = new QGraphicsPixmapItem(hit_);
    if (!facingLeft) {
        QTransform transform2;
        transform2.scale(0.06, 0.06);
        hitImage->setTransform(transform2);
        hitImage->setPos(game_->hero_->heroImage_->pos().x() + 50, game_->hero_->heroImage_->pos().y() + 17);
    } else {
        QTransform transform;
        transform.scale(-0.06, 0.06);
        hitImage->setTransform(transform);
        hitImage->setPos(game_->hero_->heroImage_->pos().x() + 56, game_->hero_->heroImage_->pos().y() + 17);
    }

    hitImage->setZValue(2);
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
    if (game_->hero_ == nullptr) return;

    pressedKeys_.remove(event->nativeScanCode());
}

void gameplayWindow::updateTimer() {
    QTime currentTime = QTime::currentTime();
    int elapsed = startTime_.secsTo(currentTime);
    QTime showTime(0, 0);
    showTime = showTime.addSecs(elapsed);
    showTime_->setText(showTime.toString("hh:mm:ss"));
}

void gameplayWindow::pauseTimer() {
    pausedTime_ = QTime::currentTime();
    gameTime_->stop();
}

void gameplayWindow::resumeTimer() {
    QTime currentTime = QTime::currentTime();
    int pauseDuration = pausedTime_.secsTo(currentTime);

    startTime_ = startTime_.addSecs(pauseDuration);

    gameTime_->start(1000);
}
