#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>
#include <QVector>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class MemoryGame : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryGame(QWidget *parent = nullptr);

private slots:
    void onCardClicked();
    void onTimerTimeout();

private:
    QGridLayout *layout;
    QVector<QPushButton*> buttons;
    QVector<int> cardValues;
    int firstIndex, secondIndex;
    QTimer *timer;
    int pairsFound;

    void setupBoard();
    void resetGame();
    void animateButton(QPushButton *button);
};

#endif // MEMORYGAME_H
