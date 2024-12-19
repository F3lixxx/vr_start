#include "apkfile.h"
#include "ui_apkfile.h"

apkfile::apkfile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::apkfile)
{
    ui->setupUi(this);
    connect(ui->pb_start, &QPushButton::clicked, this, &apkfile::connect_command);
}

void apkfile::connect_command() {
    QString adb = "C:\\platform-tools\\adb.exe";
    QProcess *package = new QProcess(this);

    QString package_name = "com.DefaultCompany.VRMultiplayer";
    // Убедитесь, что у вас правильное имя пакета и активности
    QString activity_name = "com.unity3d.player.UnityPlayerGameActivity"; // Замените на нужную активность

    // Формируем команду для запуска
    QString command = package_name + "/" + activity_name;

    package->setProgram(adb);  // Устанавливаем программу
    package->setArguments(QStringList() << "shell" << "am" << "start" << "-n" << command);  // Передаем аргументы

    package->start();

    if (!package->waitForStarted()) {
        qDebug() << "Can't start ADB:" << package->errorString();
        return;
    } else {
        qDebug() << "Program started successfully!";
    }

    connect(package, &QProcess::readyReadStandardOutput, [package]() {
        qDebug() << package->readAllStandardOutput();
    });
    qDebug() << "Package name: " << package_name;
    qDebug() << "Activity name: " << activity_name;
    qDebug() << "package: " << package;
}

apkfile::~apkfile()
{
    delete ui;
}
