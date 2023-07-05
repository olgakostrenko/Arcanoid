#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(300, 400);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() { this->close(); }

void MainWindow::on_pushButton_2_clicked() {
  gameWindow = new GameWindow(this);
  gameWindow->setWindowTitle("Arcanoid");
  gameWindow->show();
  this->hide();
}
