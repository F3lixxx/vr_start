#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // winConDev = new connectDev;
    // dbWin = new data_base;
    // parserxml = new ParserDataBase;
    // dbWin->searchInfo();
}

// void MainWindow::on_pb_check_dev_clicked()
// {
//     // winConDev->show();
// }


void MainWindow::on_pb_openDB_clicked()
{
    dbWin->show();
    // dbWin->create_DB();
    // dbWin->show_DB();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_openDBxml_clicked()
{
    // parserxml->show();
}

