#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <QList>
#include <QObject>
#include <QPainter>

class GameField : public QObject {
public:
  struct Brick {
    int x1, y1, x2, y2;
    bool isDestructible;

    Brick(int x1, int y1, int x2, int y2, bool isDestructible) {
      this->x1 = x1;
      this->y1 = y1;
      this->x2 = x2;
      this->y2 = y2;
      this->isDestructible = isDestructible;
    }
  };

  struct Ball {
    int x, y;
    double angle, speed;

    Ball() {
      x = 400;
      y = 500;
      angle = -55.0;
      speed = 4;
    }
    int next_x() { return this->x + (cos(3.14 * angle / 180) * speed); }

    int next_y() { return this->y + (sin(3.14 * angle / 180) * speed); }

    void move() {
      this->x = next_x();
      this->y = next_y();
    }
  };

  struct Pad {
    int x, y;
    Pad(int x, int y) {
      this->x = x;
      this->y = y;
    }

    void moveLeft() {
      if (this->x > 20)
        this->x += -20;
    }

    void moveRight() {
      if (this->x < 680)
        this->x += 20;
    }
  };

  GameField(QObject *parent);
  ~GameField();

  QList<Brick> brickList;
  Ball *ball;
  Pad *pad;

  void resetBallnPadPos();
  void update();
  void checkBorders();
  void checkCollisions();
  void checkPadCollisions();
};

#endif // GAMEFIELD_H
