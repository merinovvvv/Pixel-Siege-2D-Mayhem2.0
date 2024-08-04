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
#include "ghost.h"
#include "scaryghost.h"
#include "skeleton.h"
#include "slime.h"
#include "wolf.h"


gameplayWindow::gameplayWindow(Game* game, QWidget *parent)
    : QMainWindow{parent}, game_(game), view_(new QGraphicsView(this)), scene_(new QGraphicsScene(this))
{
    scene_->setSceneRect(0, 0, 1920, 1080);

    //setting the icon
    this->setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    setCursor(Qt::BlankCursor);

    // timer in the upper left corner of the screen
    showTime_ = new QLabel();
    showTime_->setStyleSheet("font-size: 35px;"
                             "color: black;");
    showTime_->setText("00:00:00");
    startTime_ = QTime::currentTime();
    gameTime_ = new QTimer();
    connect(gameTime_, SIGNAL(timeout()), this, SLOT(updateTimer()));
    gameTime_->start(1000);

    // hp bar in the upper right corner of the screen
    hpLabel_ = new QLabel();
    hpLabel_->setText("HP");
    hpLabel_->setStyleSheet("font-size: 35px;"
                            "color: black;");
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

    // spacer to separate the hp bar and the timer
    QSpacerItem* space = new QSpacerItem(1400, 0, QSizePolicy::Preferred, QSizePolicy::Fixed);
    QHBoxLayout* menuLayout = new QHBoxLayout();
    menuLayout->addWidget(showTime_);
    menuLayout->addItem(space);
    menuLayout->addWidget(hpLabel_);
    menuLayout->addWidget(healthBar_);

    // widget where the elements mentioned above are placed
    QWidget* containerWidget = new QWidget();
    containerWidget->setFixedWidth(1900);
    containerWidget->setStyleSheet("background-color: transparent;");
    containerWidget->setLayout(menuLayout);
    containerWidget->setCursor(Qt::BlankCursor);

    QGraphicsProxyWidget *toShow = scene_->addWidget(containerWidget);
    toShow->setPos(10, 10);
    toShow->setZValue(2);

    view_->setScene(scene_);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view_);

    // 60 fps monster movement
    moveTimer_ = new QTimer();
    connect(moveTimer_, SIGNAL(timeout()), this, SLOT(moveMonsters()));
    moveTimer_->start(1000 / 60);

    //spawn monsters with different interval
    ghostTimer_ = new QTimer();
    connect(ghostTimer_, SIGNAL(timeout()), this, SLOT(spawnGhost()));
    ghostTimer_->start(10 * 1000);

    scaryGhostTimer_ = new QTimer();
    connect(scaryGhostTimer_, SIGNAL(timeout()), this, SLOT(spawnScaryGhost()));
    scaryGhostTimer_->start(25 * 1000);

    skeletonTimer_ = new QTimer();
    connect(skeletonTimer_, SIGNAL(timeout()), this, SLOT(spawnSkeleton()));
    skeletonTimer_->start(5 * 1000);

    slimeTimer_ = new QTimer();
    connect(slimeTimer_, SIGNAL(timeout()), this, SLOT(spawnSlime()));
    slimeTimer_->start(15 * 1000);

    wolfTimer_ = new QTimer();
    connect(wolfTimer_, SIGNAL(timeout()), this, SLOT(spawnWolf()));
    wolfTimer_->start(40 * 1000);

    monsterHitUpdateTimer_ = new QTimer();
    connect(monsterHitUpdateTimer_, SIGNAL(timeout()), this, SLOT(monsterHit()));
    monsterHitUpdateTimer_->start(1000 * 4);
}

void gameplayWindow::setMap(QString& map) {
    map_ = map;
    QPixmap scaledMap = QPixmap(map_).scaled(1920, 1080, Qt::IgnoreAspectRatio);
    background_ = new QGraphicsPixmapItem(scaledMap);
    background_->setZValue(0);
    scene_->addItem(background_);

    if (game_->hero_ == nullptr) {
        game_->hero_ = new Hero(game_, this);
        game_->hero_->health_ = 100;
    }
}

QVector<QString> gameplayWindow::getMaps() {
    return maps_;
}

void gameplayWindow::keyPressEvent(QKeyEvent* event) {
    if (game_->hero_ == nullptr) return;

    pressedKeys_.insert(event->nativeScanCode());
    QRectF characterRect = game_->hero_->heroImage_->boundingRect();
    qreal characterLeft = characterRect.left() + game_->hero_->heroImage_->x();
    qreal characterRight = characterRect.right() + game_->hero_->heroImage_->x();
    qreal characterTop = characterRect.top() + game_->hero_->heroImage_->y(); //TODO
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
                game_->hero_->position_ += QPointF(0, 10);
                // Когда не упёрлись в левую границу и упёрлись в нижнюю
            } else if (characterLeft > mapLeft && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                game_->hero_->position_ += QPointF(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), 5 * qSqrt(2));
                game_->hero_->position_ += QPointF(-5 * qSqrt(2), 5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(0, -10);
                // Когда не упёрлись в левую границу и упёрлись в верхнюю
            } else if (characterLeft > mapLeft && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                game_->hero_->position_ += QPointF(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), -5 * qSqrt(2));
                game_->hero_->position_ += QPointF(-5 * qSqrt(2), -5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(-10, 0);
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
                game_->hero_->position_ += QPointF(0, 10);
                // Когда не упрёлись в правую и упёрлись в нижнюю границу
            } else if (characterRight < mapRight && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(10, 0);
                game_->hero_->position_ += QPointF(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), 5 * qSqrt(2));
                game_->hero_->position_ += QPointF(5 * qSqrt(2), 5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(0, -10);
                // Когда не упрёлись в правую и упёрлись в верхнюю границу
            } else if (characterRight < mapRight && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(10, 0);
                game_->hero_->position_ += QPointF(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), -5 * qSqrt(2));
                game_->hero_->position_ += QPointF(5 * qSqrt(2), -5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(10, 0);
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
                game_->hero_->position_ += QPointF(0, -10);
                // Когда не упёрлись в левую границу и упёрлись в верхнюю
            } else if (characterLeft > mapLeft && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                game_->hero_->position_ += QPointF(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), -5 * qSqrt(2));
                game_->hero_->position_ += QPointF(-5 * qSqrt(2), -5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(0, -10);
                // Когда не упрёлись в правую и упёрлись в верхнюю границу
            } else if (characterRight < mapRight && characterTop <= mapTop) {
                game_->hero_->heroImage_->moveBy(10, 0);
                game_->hero_->position_ += QPointF(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterTop > mapTop) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), -5 * qSqrt(2));
                game_->hero_->position_ += QPointF(5 * qSqrt(2), -5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(0, -10);
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
                game_->hero_->position_ += QPointF(0, 10);
                // Когда не упёрлись в левую границу и упёрлись в нижнюю
            } else if (characterLeft > mapLeft && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(-10, 0);
                game_->hero_->position_ += QPointF(-10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterLeft > mapLeft && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(-5 * qSqrt(2), 5 * qSqrt(2));
                game_->hero_->position_ += QPointF(-5 * qSqrt(2), 5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(0, 10);
                // Когда не упрёлись в правую и упёрлись в нижнюю границу
            } else if (characterRight < mapRight && characterBottom >= mapBottom) {
                game_->hero_->heroImage_->moveBy(10, 0);
                game_->hero_->position_ += QPointF(10, 0);
                // Когда не упёрлись в обе границы
            } else if (characterRight < mapRight && characterBottom < mapBottom) {
                game_->hero_->heroImage_->moveBy(5 * qSqrt(2), 5 * qSqrt(2));
                game_->hero_->position_ += QPointF(5 * qSqrt(2), 5 * qSqrt(2));
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
                game_->hero_->position_ += QPointF(0, 10);
            }
        }
        break;
    case 1:
        pauseTimer();
        //gameTime_->stop();
        game_->showPauseMenu();
        break;
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

    // Processing the hit damage
    for (auto it = game_->monsters_.begin(); it != game_->monsters_.end(); ) {
        auto monster = *it;
        if (monster->getModel()->collidesWithItem(hitImage)) {
            monster->setHealth(monster->getHealth() - 5);
            if (monster->getHealth() <= 0) {
                scene_->removeItem(monster->getModel());
                it = game_->monsters_.erase(it);
                delete monster;
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    QTimer::singleShot(100, [hitImage, this]() {
        scene_->removeItem(hitImage);
        delete hitImage;
    });

}

void gameplayWindow::monsterHit() {
    auto hero = game_->hero_;
    for (auto& monster : game_->monsters_) {
        if (monster->getModel()->collidesWithItem(hero->heroImage_)) {
            hero->health_ = hero->health_ - monster->getDamage();
            updateHealth(hero->health_);
            if (hero->health_ <= 0) {
                delete game_->gameplay_window;
                game_->gameplay_window = nullptr;
                game_->hero_ = nullptr;
                game_->monsters_.clear();
                game_->showGameOverWindow();
                return;
            }
        }
    }
}

void gameplayWindow::updateHealth(qreal health) {
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

void gameplayWindow::moveMonsters() {
    for (auto& monster : game_->monsters_) {
        monster->move(*game_->hero_);
    }
}

void gameplayWindow::pauseTimer() {
    pausedTime_ = QTime::currentTime();
    gameTime_->stop();
    moveTimer_->stop();
    ghostTimer_->stop();
    scaryGhostTimer_->stop();
    skeletonTimer_->stop();
    slimeTimer_->stop();
    wolfTimer_->stop();
    monsterHitUpdateTimer_->stop();
}

void gameplayWindow::resumeTimer() {
    QTime currentTime = QTime::currentTime();
    int pauseDuration = pausedTime_.secsTo(currentTime);

    startTime_ = startTime_.addSecs(pauseDuration);

    gameTime_->start(1000);
    moveTimer_->start(1000 / 60);
    ghostTimer_->start(10 * 1000);
    scaryGhostTimer_->start(25 * 1000);
    skeletonTimer_->start(5 * 1000);
    slimeTimer_->start(15 * 1000);
    wolfTimer_->start(40 * 1000);
    monsterHitUpdateTimer_->start(1000 / 60);
}

void gameplayWindow::spawnGhost() {
    auto ghost = new Ghost();
    QPointF position = QPointF(QRandomGenerator::global()->bounded(0, 1500), QRandomGenerator::global()->bounded(0, 900));
    ghost->setPosition(position);
    ghost->getModel()->setZValue(1);
    ghost->getModel()->setPos(position);
    scene_->addItem(ghost->getModel());

    game_->monsters_.push_back(ghost);
}

void gameplayWindow::spawnScaryGhost() {
    auto scaryGhost = new ScaryGhost();
    QPointF position = QPointF(QRandomGenerator::global()->bounded(0, 1500), QRandomGenerator::global()->bounded(0, 900));
    scaryGhost->setPosition(position);
    scaryGhost->getModel()->setZValue(1);
    scaryGhost->getModel()->setPos(position);
    scene_->addItem(scaryGhost->getModel());

    game_->monsters_.push_back(scaryGhost);
}

void gameplayWindow::spawnSkeleton() {
    auto skeleton = new Skeleton();
    QPointF position = QPointF(QRandomGenerator::global()->bounded(0, 1500), QRandomGenerator::global()->bounded(0, 900));
    skeleton->setPosition(position);
    skeleton->getModel()->setZValue(1);
    skeleton->getModel()->setPos(position);
    scene_->addItem(skeleton->getModel());

    game_->monsters_.push_back(skeleton);
}

void gameplayWindow::spawnSlime() {
    auto slime = new Slime();
    QPointF position = QPointF(QRandomGenerator::global()->bounded(0, 1500), QRandomGenerator::global()->bounded(0, 900));
    slime->setPosition(position);
    slime->getModel()->setZValue(1);
    slime->getModel()->setPos(position);
    scene_->addItem(slime->getModel());

    game_->monsters_.push_back(slime);
}

void gameplayWindow::spawnWolf() {
    auto wolf = new Wolf();
    QPointF position = QPointF(QRandomGenerator::global()->bounded(0, 1500), QRandomGenerator::global()->bounded(0, 900));
    wolf->setPosition(position);
    wolf->getModel()->setZValue(1);
    wolf->getModel()->setPos(position);
    scene_->addItem(wolf->getModel());

    game_->monsters_.push_back(wolf);
}
