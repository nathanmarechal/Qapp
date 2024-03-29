#ifndef MINESWEEPERGAMEOVERDIALOG_H
#define MINESWEEPERGAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class MinesweeperGameOverDialog;
}

class MinesweeperGameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MinesweeperGameOverDialog(QWidget *parent = nullptr);
    ~MinesweeperGameOverDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::MinesweeperGameOverDialog *ui;
};

#endif // MINESWEEPERGAMEOVERDIALOG_H
