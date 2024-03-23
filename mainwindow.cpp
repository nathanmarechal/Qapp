#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <algorithm>
#include <random>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    generateWord();
    updateScore(0);

    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::checkAnswer);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::nextWord);
    connect(ui->menuButton, &QPushButton::clicked, this, &MainWindow::on_menuButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::generateWord() {
    if (wordList.isEmpty()) {
        return;
    }

    int index = QRandomGenerator::global()->bounded(wordList.size());
    currentWord = wordList.at(index);

    QString scrambledWord = currentWord;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(scrambledWord.begin(), scrambledWord.end(), g);

    ui->scrambledWordLabel->setText(scrambledWord);
}

void MainWindow::checkAnswer() {
    bool isCorrect = ui->userInput->text().compare(currentWord, Qt::CaseInsensitive) == 0;
    QString buttonStyle = isCorrect ? "background-color: #28a745;" : "background-color: #dc3545;";
    ui->submitButton->setStyleSheet(buttonStyle);
    ui->nextButton->setStyleSheet(buttonStyle);

    QTimer::singleShot(2000, this, [this, isCorrect]() {
        QString resetStyle = "QPushButton { background-color: #007bff; color: white; border-radius: 15px; padding: 10px; font-size: 16px; } QPushButton:hover { background-color: #0056b3; }";
        ui->submitButton->setStyleSheet(resetStyle);
        ui->nextButton->setStyleSheet(resetStyle);
        if (!isCorrect) {
            return;
        }
        generateWord();
    });

    if (isCorrect) {
        updateScore(1);
    }
    ui->userInput->clear();
}
void MainWindow::nextWord() {
    if(score >= 1){
        updateScore(-1);
    }
    generateWord();
}

void MainWindow::updateScore(int points) {
    score += points;
    ui->scoreLabel->setText(QString("Score : %1").arg(score));
}

void MainWindow::on_menuButton_clicked() {
    QMessageBox::information(this, "Menu", "Retour au menu principal...");
}
