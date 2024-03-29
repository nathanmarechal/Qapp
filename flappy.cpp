#include "flappy.h"
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QKeyEvent>
#include <QRandomGenerator>

Flappy::Flappy(QWidget *parent)
    : QWidget(parent),
    showMessage(true),
    birdY(200),
    gravity(0.25),
    lift(-7.5),
    obstacleGap(200),
    obstacleWidth(80),
    score(0) {
    timer = new QTimer(this);
    messageTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Flappy::updateGame);
    connect(messageTimer, &QTimer::timeout, this, &Flappy::hideMessage);

    timer->start(30);
    messageTimer->setSingleShot(true);
    messageTimer->start(3000);

    backgroundPixmap.load("./tortue_complot2.jpeg");
    birdPixmap.load("./flap.png");
    birdPixmap = birdPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    createObstacle();
}

Flappy::~Flappy() {}

void Flappy::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(rect(), backgroundPixmap);

    if (!birdPixmap.isNull()) {
        painter.drawPixmap(birdX(), birdY, birdPixmap);
    }

    painter.setBrush(Qt::green);
    for (const QRect &obstacle : qAsConst(obstacles)) {
        painter.drawRect(obstacle);
    }

    if (showMessage) {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        painter.drawText(rect(), Qt::AlignCenter, "Press \"Space\"");
    }
}


void Flappy::updateGame() {
    birdY += gravity;
    gravity += 0.5;

    if (birdY > height() - 30 || birdY < 0) {
        resetGame();
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
    update();
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


int Flappy::birdX() const {
    return 100;
}

void Flappy::hideMessage() {
    showMessage = false;
    update();
}
