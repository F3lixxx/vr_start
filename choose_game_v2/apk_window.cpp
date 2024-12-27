#include "apk_window.h"
#include "ui_apk_window.h"

apk_window::apk_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::apk_window)
{
    ui->setupUi(this);
    connect(ui->pb_start, &QPushButton::clicked, this, &apk_window::start_apk);
}

void apk_window::start_apk(){
    QString package_name = ui->le_packageName->text();
    QString activity_name = ui->le_activName->text();
    QString apkPath = ui->le_apkPath->text();

    QProcess *path = new QProcess(this);

    path->setProgram(adb);
    path->setArguments(QStringList() << "install" + apkPath);

    path->start();

    if (!path->waitForStarted()) {
        qDebug() << "Can't start ADB:" << path->errorString();
        return;
    } else {
        qDebug() << "Program install started successfully!";
    }


    // QProcess *package = new QProcess(this);

    // // Формируем команду для запуска
    // QString command = package_name + "/" + activity_name;

    // package->setProgram(adb);  // Устанавливаем программу
    // package->setArguments(QStringList() << "shell" << "am" << "start" << "-n" << command);  // Передаем аргументы

    // package->start();

    // if (!package->waitForStarted()) {
    //     qDebug() << "Can't start ADB:" << package->errorString();
    //     return;
    // } else {
    //     qDebug() << "Program started successfully!";
    // }

    // connect(package, &QProcess::readyReadStandardOutput, [package]() {
    //     qDebug() << package->readAllStandardOutput();
    // });
    // qDebug() << "Package name: " << package_name;
    // qDebug() << "Activity name: " << activity_name;
    // qDebug() << "path: " << apkPath;
}

apk_window::~apk_window()
{
    delete ui;
}
