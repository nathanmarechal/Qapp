#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QRect>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimerEvent>
#include <QPixmap>


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
    QTimer *messageTimer;
    bool showMessage;
    QPixmap backgroundPixmap;
    QPixmap birdPixmap;
    double birdY;
    double gravity;
    double lift;
    int obstacleGap;
    int obstacleWidth;
    int score;
    QList<QRect> obstacles;

    void flap();
    void updateGame();
    void createObstacle();
    void checkCollision();
    void hideMessage();
    int birdX() const;
};
