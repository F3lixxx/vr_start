#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "second_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sec_win = new second_window(this);
    connect(ui->pb_init_new_device_game, &QPushButton::clicked, this, &MainWindow::open_window);

}

void MainWindow::open_window(){
    sec_win->show();
}

MainWindow::~MainWindow()
{
    delete ui;

}
