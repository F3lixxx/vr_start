#include "second_window.h"
#include "ui_second_window.h"

second_window::second_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::second_window)
{
    ui->setupUi(this);
    apk = new apkfile(this);

    connect(ui->pb_start, &QPushButton::clicked, this, &second_window::executeCommand);
    connect(ui->pb_start, &QPushButton::clicked, this, &second_window::open_window_apk);
}

void second_window::executeCommand(){
    QProcess *ip_add = new QProcess(this);

    QString adb = "C:\\platform-tools\\adb.exe";
    QString ip = ui->le_IP->text();
    QString port = ui->le_Port->text();

    QString connect_ip = ip + ":" + port;

        ip_add->setProgram(adb);  // Устанавливаем программу
        ip_add->setArguments(QStringList() << "connect" << connect_ip);  // Передаем аргументы

        ip_add->start();

    if (!ip_add->waitForStarted()) {
        qDebug() << "Can't start ADB:" << ip_add->errorString();
        return;
    } else {
        qDebug() << "ADB started successfully!";
    }

    connect(ip_add, &QProcess::readyReadStandardError, [ip_add]() {
        qDebug() << ip_add->readAllStandardError();
    });
    qDebug() << ip;
    qDebug() << port;
    qDebug() << adb;
}

void second_window::open_window_apk(){
    apk->show();
}


second_window::~second_window()
{
    delete ui;
}


