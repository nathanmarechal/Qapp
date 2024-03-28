#include "minesweepergame.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QCoreApplication>
#include <qdir.h>

MinesweeperGame::MinesweeperGame(QWidget *parent, int boardX, int boardY, double bombsProbability)
    : QDialog(parent), boardX(boardX), boardY(boardY), bombsProbability(bombsProbability) {

    QDir dir(QCoreApplication::applicationDirPath());
    pathToFlagIcon = dir.filePath("minesweeper/flag.png");
    pathToBombIcon = dir.filePath("minesweeper/bomb.png");
    pathToEmptyIcon = dir.filePath("minesweeper/0.png");

    if (!QFile::exists(pathToFlagIcon) || !QFile::exists(pathToBombIcon) || !QFile::exists(pathToEmptyIcon)) {
        qDebug() << "One or more icons do not exist at the specified locations.";
    }

    gameOver = new MinesweeperGameOverDialog(this);
    initializeValues();
    addGameButtons();
    initializeButtons();
    reset();
}




void MinesweeperGame::reset()
{

    initializeBoard();
    resetButtons();
    bombsRemainingLabel->setText("0/0");
    firstClick = true;
}

void MinesweeperGame::initializeValues() {
    this->boardX = boardX;
    this->boardY = boardY;
    this->bombsProbability = bombsProbability;
    setWindowTitle("Minesweeper Game");
}

void MinesweeperGame::initializeButtons() {
    buttons = new QPushButton**[boardX];
    for (int i = 0; i < boardX; ++i) {
        buttons[i] = new QPushButton*[boardY];
    }

    for (int row = 0; row < boardY; ++row) {
        for (int col = 0; col < boardX; ++col) {
            QPushButton *button = new QPushButton(this);
            buttons[col][row] = button;
            button->setFixedSize(30, 30);
            button->setIconSize(QSize(30, 30));
            button->move(col * 30, row * 30);
            connect(button, &QPushButton::clicked, this, &MinesweeperGame::leftButtonClick);
            button->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(button, &QPushButton::customContextMenuRequested, [this, button](const QPoint &) {
                int x = buttonColumn(button);
                int y = buttonRow(button);
                this->rightButtonClick(x,y,button);
            });
        }
    }
}



void MinesweeperGame::addGameButtons() {
    QPushButton *resetGameButton = new QPushButton(this);
    resetGameButton->setText("reset game");
    resetGameButton->setFixedSize(80, 30);
    resetGameButton->move((boardX)*30, 0);
    connect(resetGameButton, &QPushButton::clicked, this, &MinesweeperGame::reset);

    QPushButton *quitButton = new QPushButton(this);
    quitButton->setText("quit game");
    quitButton->setFixedSize(80, 30);
    quitButton->move((boardX)*30, 30);
    connect(quitButton, &QPushButton::clicked, this, &MinesweeperGame::quit);

    bombsRemainingLabel = new QLabel(this);
    bombsRemainingLabel->setText("0/0");
    bombsRemainingLabel->setFixedSize(50, 30);
    bombsRemainingLabel->move((boardX)*30, 60);

    QLabel *bombIconLabel = new QLabel(this);
    QPixmap bombIcon(pathToBombIcon);
    if (bombIcon.isNull()) {
        qDebug() << "Le chargement de l'image a échoué pour" << pathToBombIcon;
    } else {
        bombIconLabel->setPixmap(bombIcon.scaled(30, 30));
        bombIconLabel->move((boardX)*30+50, 60);
    }
}

void MinesweeperGame::initializeBoard() {
    board = new char*[boardX];
    for (int i = 0; i < boardX; ++i) {
        board[i] = new char[boardY];
        for(int j = 0; j < boardY; ++j) {
            board[i][j]= ' ';
        }
    }
}
void MinesweeperGame::quit(){
    hide();
    parentWidget()->parentWidget()->show();
}

void MinesweeperGame::resetButtons() {
    for (int i = 0; i < boardX; ++i) {
        for(int j = 0; j < boardY; ++j) {
            buttons[i][j]->setText("");
            buttons[i][j]->setIcon(QIcon());
        }
    }
}


void MinesweeperGame::updateBombsRemainingLabel()
{
    int nbBombs = countBombs();
    int nbFlags = countFlags();
    QString str = QString("%1/%2").arg(nbFlags).arg(nbBombs);

    qDebug()<<"nbBombs : "<<nbBombs<<", nbFlags : "<<nbFlags<<", str : "<<str;

    bombsRemainingLabel->setText(str);
}

int MinesweeperGame::countBombs()
{
    int nbBombs = 0;
    char symbol;
    for (int i = 0; i < boardX; ++i) {
        for(int j = 0; j < boardY; ++j) {
            symbol = board[i][j];
            if(symbol=='b' || symbol=='F')
                nbBombs++;
        }
    }
    return nbBombs;
}
int MinesweeperGame::countFlags()
{
    int nbFlags = 0;
    char symbol;
    for (int i = 0; i < boardX; ++i) {
        for(int j = 0; j < boardY; ++j) {
            symbol = board[i][j];
            if(symbol=='f' || symbol=='F')
                nbFlags++;
        }
    }
    return nbFlags;
}

void MinesweeperGame::leftButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int y = buttonRow(button);
        int x = buttonColumn(button);

        if(firstClick)
        {
            placeBombs(x,y);
            updateBombsRemainingLabel();
        }
        revealTile(x,y,button);
    }
    checkVictory();
}

void MinesweeperGame::rightButtonClick(int x,int y,QPushButton * button)
{
    if(firstClick)
    {
        return;
    }
    flagButton(x, y, button);
    updateBombsRemainingLabel();
}


void MinesweeperGame::checkVictory()
{
    bool gameIsOngoing = false;

    char symbol;
    for (int i = 0; i < boardX; ++i) {
        for(int j = 0; j < boardY; ++j) {
            symbol = board[i][j];
            if(symbol==' ')
            {
                gameIsOngoing = true;
                break;
            }
        }
    }

    if(!gameIsOngoing)
    {
        gameOver->show();
    }
}

int MinesweeperGame::buttonRow(QPushButton *button)
{
    return button->y() / 30;
}

int MinesweeperGame::buttonColumn(QPushButton *button)
{
    return button->x() / 30;
}

void MinesweeperGame::flagButton(int x,int y,QPushButton *button)
{
    if(board[x][y]==' ')
    {
        if(countFlags()>=countBombs())
        {
            return;
        }
        board[x][y]='f';

        QIcon ButtonIcon(pathToFlagIcon);
        button->setIcon(ButtonIcon);
    }
    else if(board[x][y]=='f')
    {
        board[x][y]=' ';
        button->setIcon(QIcon());
    }
    else if(board[x][y]=='b')
    {
        if(countFlags()>=countBombs())
        {
            return;
        }
        board[x][y]='F';

        QIcon ButtonIcon(pathToFlagIcon);
        button->setIcon(ButtonIcon);
    }
    else if(board[x][y]=='F')
    {
        board[x][y]='b';
        button->setIcon(QIcon());
    }

}

void MinesweeperGame::placeBombs(int col, int row)
{
    int nbBombs = boardX * boardY * bombsProbability;
    int numberOfRemainingTiles = boardX * boardY;
    for (int y = 0; y < boardY; ++y) {
        for (int x = 0; x < boardX; ++x) {
            if (row >= y - 1 && row <= y + 1 && col >= x - 1 && col <= x + 1) {
                numberOfRemainingTiles--;
                board[x][y] = ' ';
                continue;
            }
            generateBomb(x, y, nbBombs, numberOfRemainingTiles);
        }
    }
    firstClick = false;
}

void MinesweeperGame::generateBomb(int x, int y, int &nbBombs, int &numberOfRemainingTiles)
{
    int bombsPlaced = 0;
    double randomValue = static_cast<double>(rand()) / RAND_MAX;
    bool bombThere = randomValue < static_cast<double>(nbBombs) / numberOfRemainingTiles;
    if(bombThere)
    {
        board[x][y] = 'b';
        bombsPlaced++;
        nbBombs--;
    }
    numberOfRemainingTiles--;
}

void MinesweeperGame::revealTile(int x,int y,QPushButton *button)
{
    if(board[x][y]=='f' || board[x][y]=='F')
    {
        return;
    }
    if (board[x][y]=='b') {
        button->setIcon(QIcon(pathToBombIcon));
        gameOver->show();
    } else {
        int tileValue = countAdjacents(x,y);
        board[x][y] = static_cast<char>(tileValue + '0');





        if(tileValue==0)
        {
        button->setIcon(QIcon(pathToEmptyIcon));
            revealAdjacent(x,y);
        }
        else
        {
            QPalette palette = button->palette();

            if(board[x][y]=='1')
            {
                palette.setColor(QPalette::ButtonText, Qt::blue);
            }
            else if(board[x][y]=='2')
            {
                palette.setColor(QPalette::ButtonText, Qt::green);
            }
            else if(board[x][y]=='3')
            {
                palette.setColor(QPalette::ButtonText, Qt::red);
            }
            else if(board[x][y]=='4')
            {
                palette.setColor(QPalette::ButtonText, Qt::magenta);
            }
            else if(board[x][y]=='5')
            {
                palette.setColor(QPalette::ButtonText, QColor(255, 165, 0));
            }
            else if(board[x][y]=='6')
            {
                palette.setColor(QPalette::ButtonText, QColor(255, 165, 125));
            }
            else if(board[x][y]=='7')
            {
                palette.setColor(QPalette::ButtonText, QColor(125, 0, 0));
            }
            else if(board[x][y]=='8')
            {
                palette.setColor(QPalette::ButtonText, Qt::black);
            }


            button->setPalette(palette);

            QString str = QString::number(tileValue);
            button->setText(str);
        }
    }
}

int MinesweeperGame::countAdjacents(int x,int y)
{
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;

            int neighborX = x + i;
            int neighborY = y + j;


            if (neighborX >= 0 && neighborX < boardX && neighborY >= 0 && neighborY < boardY) {
                if (isBomb(neighborX, neighborY))
                    ++count;
            }
        }
    }

    return count;
}

void MinesweeperGame::revealAdjacent(int x,int y)
{

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;

            int neighborX = x + i;
            int neighborY = y + j;


            if (neighborX >= 0 && neighborX < boardX && neighborY >= 0 && neighborY < boardY) {

                if(board[neighborX][neighborY]==' ')
                {
                    revealTile(neighborX,neighborY,buttons[neighborX][neighborY]);
                }
            }
        }
    }
}

bool MinesweeperGame::isBomb(int x,int y)
{
    return board[x][y]=='b' || board[x][y] == 'F';
}

MinesweeperGame::~MinesweeperGame()
{
    // Destructor
}
