#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
#include <QPushButton>
#include <QVector>

class TicTacToe : public QWidget {
    Q_OBJECT

public:
    explicit TicTacToe(QWidget *parent = nullptr);

private slots:
    void handleButtonClicked();

signals:
    void gameOver(QString winner);

private:
    QVector<QVector<QPushButton*>> buttons;
    int currentPlayer;
    void initializeGameBoard();
    void updateCurrentPlayer();
    bool checkWinCondition() const;
    bool checkRowCondition() const;
    bool checkColCondition() const;
    bool checkDiagCondition() const;
    void resetGame();
    void applyStyleSheet();
    bool isDraw() const;

};

#endif // TICTACTOE_H
