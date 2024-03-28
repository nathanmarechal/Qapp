#ifndef MINESWEEPERSTART_H
#define MINESWEEPERSTART_H

#include <QDialog>
#include "minesweepergame.h"

namespace Ui {
class MinesweeperStart;
}

class MinesweeperStart : public QDialog
{
    Q_OBJECT

public:
    explicit MinesweeperStart(QWidget *parent = nullptr);
    ~MinesweeperStart();

private slots:
    void on_boardYsizeSlider_valueChanged(int value);

    void on_boardXsizeSlider_valueChanged(int value);

    void on_bombsProbabilitySlider_valueChanged(int value);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::MinesweeperStart *ui;
    MinesweeperGame * game;

    double BombsProbability = 0.2;
    int boardX = 16;
    int boardY = 16;
};

#endif // MINESWEEPERSTART_H
