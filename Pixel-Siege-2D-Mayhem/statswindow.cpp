#include <QPainter>
#include <QPaintEvent>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHeaderView>

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
    connect(backButton, SIGNAL(clicked()), this, SLOT(backSlot()));

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
    //layout->addStretch();

    QWidget *centralWidget = new QWidget(this);

    backButton->installEventFilter(this);

    //tableWidget = new QTableWidget(tableContainer);

    tableWidget = new QTableWidget(this);

    tableWidget->setStyleSheet(
        "QTableWidget {"
        "background-color: rgba(0, 0, 0, 150); "
        "color: white;"
        "font-size: 50px;"
        "}"
        "QHeaderView::section {"
        "background-color: rgb(255, 173, 30); "
        "color: black;"
        "border: 1px solid black;"
        "font-size: 70px;"
        "}"
        "QTableWidget::item {"
        "border: 1px solid black;"
        "}"
        "QScrollBar:vertical {"
        "background: rgba(0, 0, 0, 0);"
        "width: 15px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background: rgb(255, 173, 30);"
        "border: 1px solid black;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "background: rgba(0, 0, 0, 0);"
        "border: none;"
        "}"
        "QTableWidget::item:selected {"
        "border: 1px solid rgb(255, 173, 30);"
        "}"
        "QTableWidget::item:selected:!active {"
        "color: white;"
        "}"
        "QTableCornerButton::section {"
        "background-color: rgba(0,0,0,0);"
        "}"
        );

    tableWidget->installEventFilter(this);
    backButton->installEventFilter(this);


    layout->addWidget(tableWidget);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    loadJsonData();
    populateTable();

    backButton->setFocus();
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
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();

        if (obj == tableWidget && key == Qt::Key_Up) {
            QModelIndex currentIndex = tableWidget->currentIndex();
            if (currentIndex.isValid() && currentIndex.row() == 0) {
                backButton->setFocus();
                tableWidget->clearSelection();
                return true;
            }
        } else if (obj == backButton && (key == Qt::Key_Down || key == Qt::Key_Up)) {
            tableWidget->setFocus();
            tableWidget->setCurrentCell(0, 0);
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void statsWindow::loadJsonData() {
    QDir currentDir = QCoreApplication::applicationDirPath();
    currentDir.cdUp();
    currentDir.cdUp();
    currentDir.cdUp();


    QString fileName = "gameInfo.json";
    QString filePath = currentDir.filePath(fileName);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open the file.");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));
    QJsonObject jsonObj = jsonDoc.object();
    playersArray = jsonObj["players"].toArray();
}

void statsWindow::populateTable() {

    tableWidget->setRowCount(playersArray.size());
    tableWidget->setColumnCount(2);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setHorizontalHeaderLabels({"LOGIN", "BEST TIME"});
    tableWidget->setSortingEnabled(true);
    tableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < playersArray.size(); ++i) {
        QJsonObject playerObj = playersArray[i].toObject();

        QString login = playerObj["login"].toString();
        QString bestTime = playerObj.contains("best time") ? playerObj["best time"].toString() : "";

        QTableWidgetItem* loginItem = new QTableWidgetItem(login);
        QTableWidgetItem* bestTimeItem = new QTableWidgetItem(bestTime);

        loginItem->setFlags(loginItem->flags() & ~Qt::ItemIsEditable);
        loginItem->setTextAlignment(Qt::AlignCenter);
        bestTimeItem->setFlags(bestTimeItem->flags() & ~Qt::ItemIsEditable);
        bestTimeItem->setTextAlignment(Qt::AlignCenter);

        tableWidget->setItem(i, 0, loginItem);
        tableWidget->setItem(i, 1, bestTimeItem);

        // tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        // tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        tableWidget->setRowHeight(i, 100);
    }


    //tableWidget->resizeColumnsToContents();
}

void statsWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    loadJsonData();
    populateTable();
}
