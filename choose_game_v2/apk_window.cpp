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
}

apk_window::~apk_window()
{
    delete ui;
}
