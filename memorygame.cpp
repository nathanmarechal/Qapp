#include "memorygame.h"
#include <QRandomGenerator>
#include <algorithm>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

MemoryGame::MemoryGame(QWidget *parent)
    : QWidget(parent), firstIndex(-1), secondIndex(-1), pairsFound(0) {
    setMinimumSize(600, 600);
    setStyleSheet("QWidget { background-color: #222; }");

    auto *titleLabel = new QLabel("Memory Game", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #FFF; font-size: 30px; margin-bottom: 20px;");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);

    layout = new QGridLayout();
    mainLayout->addLayout(layout);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MemoryGame::onTimerTimeout);

    setupBoard();
}

void MemoryGame::setupBoard() {
    const int gridSize = 4;
    cardValues.resize(gridSize * gridSize);

    for(int i = 0; i < gridSize * gridSize; i += 2) {
        cardValues[i] = i / 2 + 1;
        cardValues[i + 1] = i / 2 + 1;
    }

    std::shuffle(cardValues.begin(), cardValues.end(), *QRandomGenerator::global());

    for(int i = 0; i < gridSize * gridSize; ++i) {
        auto *button = new QPushButton("?", this);
        button->setStyleSheet(R"(
            QPushButton {
                font-size: 24px;
                color: #EEE;
                background-color: #333;
                border-radius: 10px;
                padding: 15px;
                margin: 5px;
            }
            QPushButton:hover {
                background-color: #555;
            }
            QPushButton:disabled {
                background-color: #777;
                color: #AAA;
            }
        )");
        layout->addWidget(button, i / gridSize, i % gridSize);
        buttons.append(button);
        connect(button, &QPushButton::clicked, this, &MemoryGame::onCardClicked);
    }
}

void MemoryGame::onCardClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    int clickedIndex = buttons.indexOf(clickedButton);

    if(clickedIndex == firstIndex || timer->isActive() || !clickedButton->isEnabled()) {
        return;
    }

    animateButton(clickedButton);

    clickedButton->setText(QString::number(cardValues[clickedIndex]));
    if(firstIndex == -1) {
        firstIndex = clickedIndex;
    } else {
        secondIndex = clickedIndex;
        if(cardValues[firstIndex] == cardValues[secondIndex]) {
            pairsFound++;
            if(pairsFound == (buttons.size() / 2)) {
                resetGame();
            }
            firstIndex = secondIndex = -1;
        } else {
            timer->start();
        }
    }
}


void MemoryGame::onTimerTimeout() {
    timer->stop();
    buttons[firstIndex]->setText("?");
    buttons[secondIndex]->setText("?");
    firstIndex = secondIndex = -1;
}

void MemoryGame::resetGame() {
    std::shuffle(cardValues.begin(), cardValues.end(), *QRandomGenerator::global());
    for (auto *button : buttons) {
        button->setEnabled(true);
        button->setText("?");
    }
    pairsFound = 0;
    firstIndex = secondIndex = -1;
}

void MemoryGame::animateButton(QPushButton *button) {
    auto *effect = new QGraphicsOpacityEffect(button);
    button->setGraphicsEffect(effect);

    auto *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    connect(animation, &QPropertyAnimation::finished, effect, &QGraphicsOpacityEffect::deleteLater);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
