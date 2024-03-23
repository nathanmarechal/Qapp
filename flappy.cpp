#include "flappy.h"
#include <QPainter>
#include <QTimer>
#include <QtMath>

Flappy::Flappy(QWidget *parent) : QWidget(parent), birdY(200), gravity(0.25), lift(-7.5), obstacleGap(200), obstacleWidth(80), score(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Flappy::updateGame));
    timer->start(30);
    createObstacle();
}

void Flappy::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setBrush(Qt::yellow);
    painter.drawRect(100, birdY, 30, 30);

    painter.setBrush(Qt::green);
    for (const QRect &obstacle : qAsConst(obstacles)) {
        painter.drawRect(obstacle);
    }
}

void Flappy::updateGame() {
    birdY += gravity;
    gravity += 0.5;
    if (birdY > height()) {
        birdY = 200;
        gravity = 0.25;
    }

    QList<QRect> newObstacles;
    for (QRect &obstacle : obstacles) {
        obstacle.translate(-5, 0);
        if (obstacle.right() > 0) {
            newObstacles.append(obstacle);
        }
    }
    obstacles = newObstacles;

    if (obstacles.isEmpty() || obstacles.last().right() < width() - 300) {
        createObstacle();
    }

    checkCollision();
    update();
}

void Flappy::createObstacle() {
    int opening = QRandomGenerator::global()->bounded(height() / 4, 3 * height() / 4);
    obstacles.append(QRect(width(), 0, obstacleWidth, opening - obstacleGap / 2));
    obstacles.append(QRect(width(), opening + obstacleGap / 2, obstacleWidth, height()));
}

void Flappy::checkCollision() {
    QRect birdRect(100, birdY, 30, 30);
    for (const QRect &obstacle : obstacles) {
        if (obstacle.intersects(birdRect)) {
            QTimer::singleShot(0, this, SLOT(resetGame()));
            break;
        }
    }
}

void Flappy::resetGame() {
    birdY = 200;
    gravity = 0.25;
    obstacles.clear();
    score = 0;
    createObstacle();
}

void Flappy::flap() {
    gravity = lift;
}

void Flappy::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Space) {
        flap();
    }
}

void Flappy::timerEvent(QTimerEvent *) {
    updateGame();
}

Flappy::~Flappy() {}

