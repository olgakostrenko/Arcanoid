#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QGraphicsPixmapItem>

GameWindow::GameWindow(QWidget *parent) : QWidget(), ui(new Ui::GameWindow) {
  this->parent = parent;

  ui->setupUi(this);
  this->setFixedSize(802, 602);

  mainScene = new QGraphicsScene(ui->graphicsView);

  mainScene->setSceneRect(0, 0, 800, 600);

  ui->graphicsView->setScene(mainScene);

  gameField = new GameField(this);

  this->draw();

  gameTimer.setInterval(10);

  connect(&gameTimer, SIGNAL(timeout()), this, SLOT(update()));

  gameIsPaused = true;
}

GameWindow::~GameWindow() {
  delete ui;
  this->parent->show();
}

void GameWindow::draw() {
  mainScene->clear();
  for (int i = 0; i < gameField->brickList.size(); i++)
    mainScene->addRect(gameField->brickList[i].x1, gameField->brickList[i].y1,
                       50, 20, QPen(Qt::black),
                       QBrush(QColor("firebrick"), Qt::SolidPattern));
  QGraphicsPixmapItem *pixmapItem =
      new QGraphicsPixmapItem(QPixmap(":/img/img/Ball.png"));
  pixmapItem->setPos(gameField->ball->x - 10, gameField->ball->y - 10);
  mainScene->addItem(pixmapItem);
  mainScene->addRect(gameField->pad->x, gameField->pad->y, 100, 20,
                     QPen(Qt::black),
                     QBrush(QColor("white"), Qt::SolidPattern));
}

void GameWindow::update() {
  gameField->update();
  draw();
}

void GameWindow::closeEvent(QCloseEvent *event) {
  this->parent->show();
  QWidget::closeEvent(event);
  delete this;
}

void GameWindow::keyPressEvent(QKeyEvent *k) {
  switch (k->key()) {

  case Qt::Key_Space:
    if (gameIsPaused) {
      gameTimer.start();
      gameIsPaused = !gameIsPaused;
    } else {
      gameTimer.stop();
      gameIsPaused = !gameIsPaused;
    }
    break;

  case Qt::Key_A:
    if (!gameIsPaused)
      gameField->pad->moveLeft();
    break;

  case Qt::Key_D:
    if (!gameIsPaused)
      gameField->pad->moveRight();
    break;

  case Qt::Key_Escape:
    this->close();
    break;

  default:
    break;
  }
}
