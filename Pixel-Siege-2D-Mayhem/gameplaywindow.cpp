#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsProxyWidget>

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
    containerLayout->setContentsMargins(10, 10, 10, 10); // Задает отступы от краев контейнера

    setCentralWidget(containerWidget);


    // QGraphicsProxyWidget* proxy = scene_->addWidget(healthBar_);
    // proxy->setPos(10, 10); // Устанавливаем позицию на сцене

    view_->setScene(scene_);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setCentralWidget(view_);
}

gameplayWindow::~gameplayWindow() {
    // delete game_;
    // delete scene_;
    // delete view_;
    // delete character_;
}

void gameplayWindow::setMap(QString& map) {
    map_ = map;
    scene_->setBackgroundBrush(QPixmap(map_));
    //scene_->addPixmap(QPixmap(map_));

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

    switch (event->key()) {
    case Qt::Key_A:
        character_->moveBy(-10, 0);
        if (!facingLeft) {
            character_->setTransform(QTransform(1, 0, 0, 1, 0, 0));
            facingLeft = true;
        }
        break;
    case Qt::Key_D:
        character_->moveBy(10, 0);
        if (facingLeft) {
            character_->setTransform(QTransform(-1, 0, 0, 1, character_->boundingRect().width(), 0));
            facingLeft = false;
        }
        break;
    case Qt::Key_W:
        character_->moveBy(0, -10);
        break;
    case Qt::Key_S:
        character_->moveBy(0, 10);
        break;
    case Qt::Key_Escape:
        game_->showPauseMenu();
        break;
    case Qt::Key_Space: {
        Hit();
        break;
    }
    default:
        QMainWindow::keyPressEvent(event);
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
