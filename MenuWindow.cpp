#include "MenuWindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "flappy.h"

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

void MenuWindow::on_unscrambleGameButton_clicked()
{
    MainWindow *gameWindow = new MainWindow(this);
    gameWindow->show();
}

void MenuWindow::on_flappyGameButton_clicked()
{
    Flappy *flappyGame = new Flappy();
    flappyGame->show();
}
