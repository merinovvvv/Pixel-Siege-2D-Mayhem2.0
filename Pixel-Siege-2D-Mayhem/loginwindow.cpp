#include <QGraphicsDropShadowEffect>
#include <QPaintEvent>
#include <QApplication>
#include <QMessageBox>
#include <fstream>
#include <QTimer>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>

#include "loginwindow.h"
#include "game.h"
#include "json.hpp"

loginWindow::loginWindow(Game* game, QWidget *parent) : QMainWindow(parent), game_(game)
{
    setMouseTracking(true);
    setWindowIcon(QIcon(":/icon/helmetIcon.jpg"));
    //showFullScreen();
    connect(background, &QMovie::frameChanged, this, QOverload<>::of(&QMainWindow::update));
    background->start();

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);

    // Увеличиваем ширину leftSpacer
    leftSpacer = new QSpacerItem(100, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
    gridLayout->addItem(leftSpacer, 0, 0, 1, 1);

    verticalLayout = new QVBoxLayout();
    verticalLayout->addSpacing(15);

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
                          "QLabel {"
                          "color: white;"
                          "font-size: 50px;"
                          "}"
                          "QLineEdit {"
                          "background: white;"
                          "color: black;"
                          "font-size: 50px;"
                          "border: 1px solid gray;"
                          "}"
                          "QLineEdit:focus {"
                          "background: rgb(255, 173, 30);"
                          "color: black;"
                          "}"
                          );


    QHBoxLayout* loginLayout = new QHBoxLayout();

    loginLabel = new QLabel("LOGIN");
    loginLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    loginLabel->setStyleSheet(styleSheet);

    loginLineEdit = new QLineEdit();
    loginLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    loginLineEdit->setStyleSheet(styleSheet);

    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginLineEdit);

    QHBoxLayout* passwordLayout = new QHBoxLayout();

    passwordLabel = new QLabel("PASSWORD");
    passwordLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    passwordLabel->setStyleSheet(styleSheet);

    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    passwordLineEdit->setStyleSheet(styleSheet);

    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);

    authoButton = new QPushButton("AUTHORIZE");
    authoButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(authoButton, SIGNAL(clicked()), this, SLOT(authorizationSlot()));

    backButton = new QPushButton("BACK");
    backButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backSlot()));

    exitButton = new QPushButton("EXIT");
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));

    authoButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect1->setColor(Qt::black);
    effect1->setOffset(4, 4);  // Увеличение смещения для большей толщины
    authoButton->setGraphicsEffect(effect1);

    backButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect;
    effect3->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect3->setColor(Qt::black);
    effect3->setOffset(4, 4);  // Увеличение смещения для большей толщины
    backButton->setGraphicsEffect(effect3);

    exitButton->setStyleSheet(styleSheet);
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(10);  // Увеличение радиуса размытия для большей толщины
    effect2->setColor(Qt::black);
    effect2->setOffset(4, 4);  // Увеличение смещения для большей толщины
    exitButton->setGraphicsEffect(effect2);

    verticalLayout->addLayout(loginLayout, 0);
    verticalLayout->addLayout(passwordLayout, 0);
    verticalLayout->addWidget(authoButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(backButton, 0, Qt::AlignCenter);
    verticalLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    // Добавляем verticalLayout в сетку
    QWidget* buttonsWidget = new QWidget(this);
    buttonsWidget->setLayout(verticalLayout);
    gridLayout->addWidget(buttonsWidget, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignCenter);
    centralWidget->setLayout(gridLayout);

    authoButton->installEventFilter(this);
    exitButton->installEventFilter(this);
    backButton->installEventFilter(this);
}

void loginWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    // Draw the current frame of the gif
    if (!background->currentPixmap().isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background->currentPixmap());
    }
}

void loginWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusedWidget = focusWidget();
        QPushButton *focusedButton = qobject_cast<QPushButton *>(focusedWidget);
        if (focusedButton) {
            if (focusedButton == authoButton) {
                authorizationSlot();
            } else if (focusedButton == exitButton) {
                exitSlot();
            } else if (focusedButton == backButton) {
                backSlot();
            }
        }
    } else if (event->key() == Qt::Key_Escape) {
        backSlot();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void loginWindow::exitSlot() {
    QApplication::quit();
}

bool loginWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        authoButton->clearFocus();
        exitButton->clearFocus();
        backButton->clearFocus();

        QPushButton *currentButton = qobject_cast<QPushButton*>(obj);
        if (currentButton) {
            currentButton->setFocus();
        }
    }
    return QObject::eventFilter(obj, event);
}

void loginWindow::authorizationSlot() {
    authorization();
}

bool loginWindow::playerExists() {

    QDir currentDir = QCoreApplication::applicationDirPath();
    currentDir.cdUp();  // Переход на уровень вверх
    currentDir.cdUp();
    currentDir.cdUp();


    QString fileName = "gameInfo.json";
    QString filePath = currentDir.filePath(fileName);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open JSON file.";
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(jsonData));
    if (!doc.isObject()) {
        qDebug() << "JSON data is not an object.";
        return false;
    }

    QJsonObject jsonObject = doc.object();

    if (!jsonObject.contains("players") || !jsonObject["players"].isArray()) {
        qDebug() << "No 'players' array found in JSON data.";
        return false;
    }

    QJsonArray playersArray = jsonObject["players"].toArray();

    for (const QJsonValue& value : playersArray) {
        if (!value.isObject()) {
            qDebug() << "JSON value is not an object.";
            continue;
        }

        QJsonObject player = value.toObject();

        if (player.contains("login") && player.contains("password")) {
            QString login = loginLineEdit->text();
            QString password = passwordLineEdit->text();

            if (player["login"].toString() == login && player["password"].toString() == password) {
                return true;
            }
        }
    }

    return false;
}

void loginWindow::authorization() {

    QDir currentDir = QCoreApplication::applicationDirPath();
    currentDir.cdUp();  // Переход на уровень вверх
    currentDir.cdUp();
    currentDir.cdUp();


    QString fileName = "gameInfo.json";
    QString filePath = currentDir.filePath(fileName);
;

    // QFile file(filePath);
    // if (!file.exists()) {
    //     qDebug() << "File does not exist. Creating a new file.";
    //     if (!file.open(QIODevice::WriteOnly)) {
    //         QMessageBox::critical(this, "Error", "Unable to create file: " + filePath);
    //         return;
    //     }
    //     nlohmann::json initialJson = nlohmann::json::object();
    //     file.write(initialJson.dump(4).c_str());
    //     file.close();
    // }

    if (!playerExists()) {
        if (game_->senderButton == 1) {
            std::ifstream inFile(filePath.toStdString());
            if (inFile.is_open()) {
                try {
                    inFile >> game_->game_info;
                } catch (const nlohmann::json::parse_error& e) {
                    QMessageBox::critical(this, "Error", "Failed to parse JSON file: " + QString(e.what()));
                    inFile.close();
                    return;
                }
                inFile.close();
            } else {
                game_->game_info = nlohmann::json::object();
            }

            if (!game_->game_info.contains("players")) {
                game_->game_info["players"] = nlohmann::json::array();
            }

            bool playerFound = false;
            for (const auto& player : game_->game_info["players"]) {
                if (player.contains("login") && player.contains("password")) {
                    if (player["login"] == loginLineEdit->text().toStdString()) {
                        playerFound = true;
                        break;
                    }
                }
            }

            if (playerFound) {
                QMessageBox::warning(this, "Warning", "A player with the given nickname has already been registered. Choose another one.");
                loginLineEdit->setText("");
                passwordLineEdit->setText("");
                game_->login_window->close();
                game_->showLoginWindow();
            } else {
                nlohmann::json player;
                player["login"] = loginLineEdit->text().toStdString();
                player["password"] = passwordLineEdit->text().toStdString();

                game_->game_info["players"].push_back(player);

                std::ofstream outFile(filePath.toStdString(), std::ios::out | std::ios::trunc);
                if (outFile.is_open()) {
                    outFile << game_->game_info.dump(4);
                    outFile.close();
                    game_->currentPlayer = loginLineEdit->text();
                    if(game_) {
                        game_->showMainMenu();
                    }
                    this->close();
                } else {
                    QMessageBox::critical(this, "Error", "Unable to open file for writing.");
                    exit(0);
                }
            }
        } else if (game_->senderButton == 0) {
            QMessageBox::warning(this, "Warning", "There is no player with given login. Try again.");
            loginLineEdit->setText("");
            passwordLineEdit->setText("");
            game_->login_window->close();
            game_->showLoginWindow();
        }
    } else if (playerExists()) {
        if (game_->senderButton == 1) {
            QMessageBox::information(this, "Info", "Such a player already exists.");
            loginLineEdit->setText("");
            passwordLineEdit->setText("");
            game_->login_window->close();
            game_->showLoginWindow();

        } else if (game_->senderButton == 0) {
            game_->currentPlayer = loginLineEdit->text();
            if(game_) {
                game_->showMainMenu();
            }
            this->close();
        }
    }
}

void loginWindow::backSlot() {
    if(game_) {
        game_->startApplication();
    }
    this->close();
}

void loginWindow::clearFields() {
    loginLineEdit->clear();
    passwordLineEdit->clear();
}

void loginWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);
    clearFields();
}
