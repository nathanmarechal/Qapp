#ifndef MINESWEEPERGAME_H
#define MINESWEEPERGAME_H

#include <QDialog>
#include <QPushButton>
#include "minesweepergameoverdialog.h"
#include <QLabel>

class MinesweeperGame : public QDialog {
    Q_OBJECT

public:
    MinesweeperGame(QWidget *parent = nullptr, int boardX = 0, int boardY = 0, double bombsProbability = 0.0);
    ~MinesweeperGame();
    void reset();
    void quit();

private slots:
    void leftButtonClick();
    void rightButtonClick(int x, int y, QPushButton* button);

private:
    int boardX;
    int boardY;
    double bombsProbability;
    char** board;
    QPushButton*** buttons;
    bool firstClick = true;
    QString pathToFlagIcon;
    QString pathToBombIcon;
    QString pathToEmptyIcon;
    QLabel* bombsRemainingLabel;
    MinesweeperGameOverDialog* gameOver;

    void initializeValues();
    void initializeButtons();
    void addGameButtons();
    void initializeBoard();
    void resetButtons();
    void flagButton(int x, int y, QPushButton* button);
    void placeBombs(int x, int y);
    void generateBomb(int x, int y, int& nbBombs, int& numberOfRemainingTiles);
    void revealTile(int x, int y, QPushButton* button);
    int countAdjacents(int x, int y);
    void revealAdjacent(int x, int y);
    bool isBomb(int x, int y);
    void updateBombsRemainingLabel();
    int countBombs();
    int countFlags();
    void checkVictory();

    int buttonRow(QPushButton* button);
    int buttonColumn(QPushButton* button);
};

#endif // MINESWEEPERGAME_H
