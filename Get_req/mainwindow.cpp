#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this,
            [=](QNetworkReply *reply){
                if(reply -> error()){
                qDebug() << reply -> errorString();
                    return;
                }
                QString answer = reply->readAll();
                qDebug() << answer;
            }
        );
    connect(ui->pb_connect, &QPushButton::clicked, this, &MainWindow::click_start);
}

void MainWindow::click_start(){
    request_url();
}

void MainWindow::request_url(){
    request.setUrl(QUrl("http://192.168.0.9:8080?packageName=com.dideploy.lettore.debug&activityName=com.dideploy.lettore.AuthenticationActivity"));
    manager->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}
