#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbWin = new data_base;
}



void MainWindow::on_pb_openDB_clicked()
{
    dbWin->show();
}

void MainWindow::on_pb_openDBxml_clicked()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}



