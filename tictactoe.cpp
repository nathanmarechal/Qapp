#include "tictactoe.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QGraphicsDropShadowEffect>
#include <QFont>
#include <QMessageBox>


TicTacToe::TicTacToe(QWidget *parent) : QWidget(parent), currentPlayer(1) {
    setWindowTitle("Tic Tac Toe");
    setMinimumSize(600, 400); // Agrandir la fenêtre

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Tic Tac Toe");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(R"(
        font-size: 36px;
        font-weight: bold;
        margin: 20px;
    )");

    mainLayout->addWidget(titleLabel);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);
    initializeGameBoard();

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            gridLayout->addWidget(buttons[row][col], row, col);
            connect(buttons[row][col], &QPushButton::clicked, this, &TicTacToe::handleButtonClicked);
        }
    }

    mainLayout->addLayout(gridLayout);
    applyStyleSheet();
}

void TicTacToe::initializeGameBoard() {
    buttons.resize(3);
    for (int row = 0; row < 3; ++row) {
        buttons[row].resize(3);
        for (int col = 0; col < 3; ++col) {
            buttons[row][col] = new QPushButton("");
            buttons[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons[row][col]->setFont(QFont("Arial", 24));

            // Ajout de l'effet d'ombre
            QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
            shadowEffect->setBlurRadius(5);
            shadowEffect->setColor(Qt::black);
            shadowEffect->setOffset(2);
            buttons[row][col]->setGraphicsEffect(shadowEffect);
        }
    }
}

void TicTacToe::handleButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button && button->text().isEmpty()) {
        button->setText(currentPlayer == 1 ? "X" : "O");
        if (checkWinCondition()) {
            QString winnerName = currentPlayer == 1 ? "Player X wins!" : "Player O wins!";
            QMessageBox::information(this, "Game Over", winnerName);
            resetGame();
        } else if (isDraw()) {
            QMessageBox::information(this, "Game Over", "It's a draw!");
            resetGame();
        } else {
            updateCurrentPlayer();
        }
    }
}

bool TicTacToe::isDraw() const {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (buttons[row][col]->text().isEmpty()) {
                return false; // Il reste des coups possibles.
            }
        }
    }
    return true; // Plus aucun coup possible.
}

void TicTacToe::applyStyleSheet() {
    this->setStyleSheet(R"(
        QPushButton {
            border: 2px solid #007AFF;
            border-radius: 15px;
            background-color: #007AFF;
            color: white;
            padding: 5px 10px;
            font-size: 24px;
            min-height: 100px;
            min-width: 100px;
        }
        QPushButton:hover {
            background-color: #0051A8;
        }
        QPushButton:pressed {
            background-color: #003D7A;
        }
        QPushButton:disabled {
            background-color: #cccccc;
            border-color: #cccccc;
            color: #666666;
        }
    )");
}

void TicTacToe::updateCurrentPlayer()
{
    currentPlayer = (currentPlayer % 2) + 1;
}

bool TicTacToe::checkWinCondition() const
{
    return checkRowCondition() || checkColCondition() || checkDiagCondition();
}

bool TicTacToe::checkRowCondition() const
{
    for (int row = 0; row < 3; ++row) {
        if (!buttons[row][0]->text().isEmpty() &&
            buttons[row][0]->text() == buttons[row][1]->text() &&
            buttons[row][1]->text() == buttons[row][2]->text()) {
            return true;
        }
    }
    return false;
}

bool TicTacToe::checkColCondition() const
{
    for (int col = 0; col < 3; ++col) {
        if (!buttons[0][col]->text().isEmpty() &&
            buttons[0][col]->text() == buttons[1][col]->text() &&
            buttons[1][col]->text() == buttons[2][col]->text()) {
            return true;
        }
    }
    return false;
}

bool TicTacToe::checkDiagCondition() const
{
    if (!buttons[0][0]->text().isEmpty() &&
        buttons[0][0]->text() == buttons[1][1]->text() &&
        buttons[1][1]->text() == buttons[2][2]->text()) {
        return true;
    }

    if (!buttons[0][2]->text().isEmpty() &&
        buttons[0][2]->text() == buttons[1][1]->text() &&
        buttons[1][1]->text() == buttons[2][0]->text()) {
        return true;
    }

    return false;
}

void TicTacToe::resetGame() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col]->setText("");
            buttons[row][col]->setEnabled(true);
        }
    }
    currentPlayer = 1;
}
