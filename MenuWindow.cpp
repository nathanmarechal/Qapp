#include "MenuWindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "flappy.h"
#include "tictactoe.h"
#include "memorygame.h"
#include <QDebug>

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)


{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_unscrambleGameButton_clicked() {
    static MainWindow* gameWindow = nullptr;
    if (!gameWindow) {
        gameWindow = new MainWindow(this);
        gameWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(gameWindow, &QWidget::destroyed, this, []() { gameWindow = nullptr; });
    }
    gameWindow->show();
    gameWindow->raise();
    gameWindow->activateWindow();
}

void MenuWindow::on_flappyGameButton_clicked() {
    static Flappy *flappyGame = nullptr;
    if (!flappyGame) {

        flappyGame = new Flappy();
        flappyGame->setAttribute(Qt::WA_DeleteOnClose);
        connect(flappyGame, &Flappy::destroyed, [=]() {
            flappyGame = nullptr;
        });
    }

    flappyGame->show();
    flappyGame->raise();
    flappyGame->activateWindow();
}

void MenuWindow::on_tictactoeGameButton_clicked()
{
    TicTacToe *tictactoeGame = new TicTacToe(nullptr);
    tictactoeGame->show();
}

void MenuWindow::on_memoryGameButton_clicked() {
    qDebug() << "Jeu de mémoire cliqué";
    static MemoryGame* memoryGame = nullptr;
    if (!memoryGame) {
        memoryGame = new MemoryGame(); // Suppression de 'this' pour éviter une éventuelle intégration incorrecte comme widget enfant.
        memoryGame->setAttribute(Qt::WA_DeleteOnClose);
        memoryGame->setWindowFlag(Qt::Window); // Assure que memoryGame est traité comme une fenêtre indépendante.
        connect(memoryGame, &QWidget::destroyed, [=]() {
            memoryGame = nullptr;
        });
    }
    memoryGame->show();
    memoryGame->raise();
    memoryGame->activateWindow();
}
