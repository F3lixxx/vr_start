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
    connect(ui->pb_devices, &QPushButton::clicked, this, &MainWindow::connected_devices);

}

void MainWindow::connected_devices(){
      QProcess *devices = new QProcess(this);

      QString adb = "C:\\platform-tools\\adb.exe";
      devices->setProgram(adb);  // Устанавливаем программу
      devices->setArguments(QStringList() << "devices" );  // Передаем аргументы

      devices->start();

      if (!devices->waitForStarted()) {
          qDebug() << "Can't start ADB:" << devices->errorString();
          return;
      } else {
          qDebug() << "ADB started successfully!";
      }

      connect(devices, &QProcess::readyReadStandardError, [devices]() {
          qDebug() << devices->readAllStandardError();
      });

      connect(devices, &QProcess::readyReadStandardOutput, this, &MainWindow::readOutput);
      connect(devices, &QProcess::readyReadStandardError, this, &MainWindow::readError);
}

void MainWindow::readOutput() {
    // Чтение стандартного вывода
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process) {
        QByteArray output = process->readAllStandardOutput();
        QString outputStr = QString::fromUtf8(output);

        // Ищем строку с уровнем заряда
        QStringList lines = outputStr.split("\n");
        for (const QString &line : lines) {
            if (line.contains("level")) {
                qDebug() << "Battery level: " << line.trimmed();
                break;
            }
        }
        ui->te_adb_devices->append(QString(output));  // Добавляем в QTextEdit
    }
}

void MainWindow::readError() {
    // Чтение стандартного вывода ошибок
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process) {
        QByteArray error = process->readAllStandardError();
        qDebug() << "Error: " << error;  // Логируем ошибки
    }
}

void MainWindow::open_window(){
    sec_win->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
