#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sec_win = new second_window(this);
    add_device = new add_new_devices(this);

    model = new QSqlTableModel(this);
    model->setTable("Devices");
    model->select();
    ui->tv_device_db->setModel(model);
    // connect(ui->pb_choose_device, &QPushButton::clicked, this, &MainWindow::window_choose_game);
    // connect(ui->pb_check_new_device, &QPushButton::clicked, this, &MainWindow::window_install_device);
    // connect(ui->pb_devices, &QPushButton::clicked, this, &MainWindow::on_pb_devices_clicked);

}

void MainWindow::readOutput() {
    // Чтение стандартного вывода
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process) {
        QByteArray output = process->readAllStandardOutput();
        QString outputStr = QString::fromUtf8(output);

        process->start("adb",  QStringList() << "shell" << "dumpsys" << "battery");
        if (!process->waitForFinished()) {
            qWarning() << "Команда для получения модели устройства не выполнена!";
            return;
        }

        // Ищем строку с уровнем заряда
        QStringList lines = outputStr.split("\n");
        for (const QString &line : lines) {
            if (line.contains("level")) {
                qDebug() << "Battery level: " << line.trimmed();
                break;
            }
        }
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

MainWindow::~MainWindow()
{
    delete ui;
}



