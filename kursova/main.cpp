#include "gamewindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  a.setWindowIcon(QIcon(":/img/img/face 1.png"));
  w.setWindowTitle("Arcanoid");

  return a.exec();
}
