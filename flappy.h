#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QRect>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimerEvent>


class Flappy : public QWidget
{
    Q_OBJECT

public:
    explicit Flappy(QWidget *parent = nullptr);
    ~Flappy();

public slots:
    void resetGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    QTimer *timer;
    int birdY;
    qreal gravity;
    qreal lift;
    QList<QRect> obstacles;
    int obstacleGap;
    int obstacleWidth;
    int score;

    void flap();
    void updateGame();
    void createObstacle();
    void checkCollision();
};
