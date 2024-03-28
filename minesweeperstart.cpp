#include "minesweeperstart.h"
#include "ui_minesweeperstart.h"

#include <QString>
#include<QDebug>

MinesweeperStart::MinesweeperStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MinesweeperStart)
{
    ui->setupUi(this);

    ui->bombsProbabilitySlider->setValue(BombsProbability * 100);
    ui->boardXsizeSlider->setValue(boardX);
    ui->boardYsizeSlider->setValue(boardY);

    ui->bombsProbabilitySlider->setMinimum(3);
    ui->bombsProbabilitySlider->setMaximum(97);
    ui->boardXsizeSlider->setMinimum(4);
    ui->boardXsizeSlider->setMaximum(50);
    ui->boardYsizeSlider->setMinimum(4);
    ui->boardYsizeSlider->setMaximum(50);





    QString str = QString::number(BombsProbability);
    ui->bombsProbabilityValue->setText(str);

    str = QString::number(boardX);
    ui->boardXSizeValue->setText(str);

    str = QString::number(boardY);
    ui->boardYSizeValue->setText(str);



}

MinesweeperStart::~MinesweeperStart()
{
    delete ui;
}

void MinesweeperStart::on_boardYsizeSlider_valueChanged(int value)
{
    boardY = value;
    QString str = QString::number(boardY);
    ui->boardYSizeValue->setText(str);
}


void MinesweeperStart::on_boardXsizeSlider_valueChanged(int value)
{
    boardX = value;
    QString str = QString::number(boardX);
    ui->boardXSizeValue->setText(str);
}


void MinesweeperStart::on_bombsProbabilitySlider_valueChanged(int value)
{
    BombsProbability = value / 100.0;
    QString str = QString::number(BombsProbability);
    ui->bombsProbabilityValue->setText(str);
}


void MinesweeperStart::on_buttonBox_rejected()
{
    hide();
    parentWidget()->show();
}


void MinesweeperStart::on_buttonBox_accepted()
{
    qDebug( "before" );
    hide();
    game = new MinesweeperGame(this,boardX,boardY,BombsProbability);
    game->show();
    qDebug( "after" );
}

