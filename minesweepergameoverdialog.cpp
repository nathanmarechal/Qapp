#include "minesweepergameoverdialog.h"
#include "ui_minesweepergameoverdialog.h"
#include "minesweepergame.h"

MinesweeperGameOverDialog::MinesweeperGameOverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MinesweeperGameOverDialog)
{
    ui->setupUi(this);
}

MinesweeperGameOverDialog::~MinesweeperGameOverDialog()
{
    delete ui;
}

void MinesweeperGameOverDialog::on_buttonBox_rejected()
{
    hide();
    MinesweeperGame *gameWidget = qobject_cast<MinesweeperGame*>(parentWidget());
    if (gameWidget) {
        gameWidget->quit();
    }
}


void MinesweeperGameOverDialog::on_buttonBox_accepted()
{
    MinesweeperGame *gameWidget = qobject_cast<MinesweeperGame*>(parentWidget());
    if (gameWidget) {
        gameWidget->reset();
    }
}

