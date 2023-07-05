#include "gamefield.h"
#include <QApplication>
#include <QFont>
#include <QFontMetrics>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <iostream>

GameField::GameField(QObject *parent) : QObject(parent) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 14; j++) {
      brickList.append(
          Brick(50 + j * 50, 100 + i * 20, 100 + j * 50, 120 + i * 20, true));
    }
  }

  ball = new Ball;
  pad = new Pad(360, 550);
}

GameField::~GameField() {
  brickList.clear();
  delete ball;
}

void GameField::resetBallnPadPos() {
  ball->x = 400;
  ball->y = 500;
  pad->x = 360;
  pad->y = 550;
}

void GameField::update() {
  checkBorders();
  checkCollisions();
  checkPadCollisions();
  ball->move();
}

void GameField::checkBorders() {

  if (ball->next_x() < 10 || ball->next_x() > 790) {
    ball->angle = 180 - ball->angle;
    std::cout << ball->angle << std::endl;
  }
  if (ball->next_y() < 10 || ball->next_y() > 590) {
    ball->angle = 0 - ball->angle;
    std::cout << ball->angle << std::endl;
  }
  if (ball->next_y() > 560) {

    resetBallnPadPos();
    ball->move();
    return;
  }
}

void GameField::checkCollisions() {
  for (int i = 0; i < brickList.size(); i++) {
    bool collisionPerformed = false;
    if (ball->next_x() > brickList[i].x1 - 11 &&
        ball->next_x() < brickList[i].x2 + 11 &&
        ball->next_y() > brickList[i].y1 - 11 &&
        ball->next_y() < brickList[i].y2 + 11) {

      if (ball->x < brickList[i].x1 && !collisionPerformed) {
        ball->angle = 180 - ball->angle;
        collisionPerformed = true;
      }
      if (ball->x > brickList[i].x2 && !collisionPerformed) {
        ball->angle = 180 - ball->angle;
        collisionPerformed = true;
      }

      if (ball->y < brickList[i].y1 && !collisionPerformed) {
        ball->angle = 0 - ball->angle;
        collisionPerformed = true;
      }
      if (ball->y > brickList[i].y2 && !collisionPerformed) {
        ball->angle = 0 - ball->angle;
        collisionPerformed = true;
      }
      if (brickList[i].isDestructible)
        brickList.removeAt(i);
      if (brickList.isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            nullptr, "Кінець гри",
            "Всі цеглинки зруйновані! Чи бажаєте зіграти ще?",
            QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::No) {

          QApplication::quit();

        } else {

          for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 14; j++) {
              brickList.append(Brick(50 + j * 50, 100 + i * 20, 100 + j * 50,
                                     120 + i * 20, true));
            }
          }

          ball = new Ball;
          pad = new Pad(360, 550);
        }
      }
    }
    if (collisionPerformed)
      break;
  }

  if (ball->angle > 360)
    ball->angle -= 360;
  if (ball->angle < -360)
    ball->angle += 360;
}

void GameField::checkPadCollisions() {

  bool collisionPerformed = false;

  if (ball->next_x() > pad->x - 11 && ball->next_x() < pad->x + 111 &&
      ball->next_y() > pad->y - 11 && ball->next_y() < pad->y + 31) {
    if (ball->x < pad->x && !collisionPerformed) {
      ball->angle = 180 - ball->angle;
      collisionPerformed = true;
    }
    if (ball->x > pad->x + 100 && !collisionPerformed) {
      ball->angle = 180 - ball->angle;
      collisionPerformed = true;
    }

    if (ball->y < pad->y && !collisionPerformed) {
      ball->angle = 0 - ball->angle;
      collisionPerformed = true;
    }
    if (ball->y > pad->y + 20 && !collisionPerformed) {
      ball->angle = 0 - ball->angle;
      collisionPerformed = true;
    }
  }

  if (ball->angle > 360)
    ball->angle -= 360;
  if (ball->angle < -360)
    ball->angle += 360;
}
