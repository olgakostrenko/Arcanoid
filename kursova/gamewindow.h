#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>

#include "gamefield.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget {
  Q_OBJECT

public:
  GameWindow(QWidget *parent);
  ~GameWindow();
  void keyPressEvent(QKeyEvent *k);

private:
  QWidget *parent;
  Ui::GameWindow *ui;
  QGraphicsScene *mainScene;
  GameField *gameField;
  QTimer gameTimer;
  bool gameIsPaused;

  void draw();
  void closeEvent(QCloseEvent *event);

private slots:
  void update();
};

#endif // GAMEWINDOW_H
