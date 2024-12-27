#include "connectdev.h"
#include "ui_connectdev.h"

connectDev::connectDev(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::connectDev)
{
    ui->setupUi(this);
    this->setWindowTitle("Connected Devices");
    connect(ui->pb_checkDevice, &QPushButton::clicked, this, &connectDev::connected_dev);
    connect(ui->pb_setPort, &QPushButton::clicked, this, &connectDev::set_port);
}

void connectDev::connected_dev(){
    QProcess *devices = new QProcess(this);

    devices->setProgram(adb);
    devices->setArguments(QStringList() << "devices");

    QString command = adb + " " + devices->arguments().join(" ");
    qDebug() << "Executing command:" << command;

    connect (devices, &QProcess::readyReadStandardOutput, this, [this, devices](){
        QByteArray output = devices->readAllStandardOutput();
        ui->te_devices->append(QString::fromUtf8(output));
    });

    connect (devices, &QProcess::readyReadStandardError, this, [this, devices](){
        QByteArray errorOutput = devices->readAllStandardError();
        ui->te_devices->append(QString::fromUtf8(errorOutput));
    });

    devices->start();

    if(!devices->waitForFinished()){
        qDebug() << "Can't start ADB" << devices->errorString();
    }else{
        qDebug() << "ADB start successfully!";
    }
    devName();
    getIP();
    // set_port();
    ui->te_devices->append(QString());
}



bool connectDev::isDeviceConnected(const QString& ipAddress) {
    QProcess checkProcess;
    QString adbPath = QCoreApplication::applicationDirPath() + "/platform-tools/adb.exe";
    checkProcess.setProgram(adbPath);
    checkProcess.setArguments(QStringList() << "devices");
    checkProcess.start();
    checkProcess.waitForFinished();

    QString output = QString::fromUtf8(checkProcess.readAllStandardOutput());
    // Используем регулярное выражение для точного совпадения "ip:port device"
    QRegularExpression re(ipAddress + ":5555\\s+device");
    QRegularExpressionMatch match = re.match(output);

    if(!checkProcess.waitForFinished()){
        qDebug() << "Can't start command adb devices" << checkProcess.errorString();
    }else{
        qDebug() << "ADB start command adb devices!";
    }

    return match.hasMatch();
}

QString connectDev::devName(){
    QProcess devices (this);

    devices.setProgram(adb);
    devices.setArguments(QStringList() << "shell" << "getprop" << "ro.product.model");
    QString error = "can't get name";
    // Составляем строку команды для вывода в qDebug
    QString command = adb + " " + devices.arguments().join(" ");
    qDebug() << "Executing command:" << command;
    devices.start();

    if(!devices.waitForFinished()){
        qDebug() << "Can't start command adb shell getprop ro.product.model" << devices.errorString();
        return error;
    }else{
        qDebug() << "ADB start command adb shell getprop ro.product.model!";
    }

    QString outputStr = QString::fromUtf8(devices.readAllStandardOutput()).trimmed();
    if (outputStr.isEmpty()) {
        qWarning() << "Модель устройства не найдена!";
    }else{
        qDebug() << outputStr;
    }
    deviceName = outputStr;
    return deviceName;
}

int connectDev::set_port(){
    QProcess set_port(this);

    set_port.setProgram(adb);
    set_port.setArguments(QStringList() << "tcpip" << "5555");

    set_port.start();
    if(!set_port.waitForFinished()){
        qDebug() << "Can't start command adb tcpip 5555" << set_port.errorString();
        return -1;
    }else{
        qDebug() << "ADB start command adb tcpip 5555!";
    }

    ui->te_devices->append(QString::fromUtf8(set_port.readAllStandardOutput()));
    port = 5555;
    qDebug() << "IP-адрес устройства:" << port;
    return port;
}

QString connectDev::getIP(){
    QProcess process_get_IP(this);

    process_get_IP.setProgram(adb);
    QStringList arguments = QStringList() << "shell" << "ip" << "addr" << "show" << "wlan0";
    process_get_IP.setArguments(arguments);

    QString command = adb + " " + process_get_IP.arguments().join(" ");
    qDebug() << "Executing command:" << command;
    process_get_IP.start();

    if (!process_get_IP.waitForFinished()) {
        qWarning() << "Не удалось получить IP-адрес!";
    }else{
        qDebug() << "ADB start command adb shell ip addr show wlan0!";
    }

    QString outputStr = QString::fromUtf8(process_get_IP.readAllStandardOutput());
    QStringList lines = outputStr.split('\n');

    for (const QString &line : lines) {
        if (line.contains("inet ")) {
                QStringList parts = line.split(' ', Qt::SkipEmptyParts);
                get_IP = parts[1].split('/')[0];
                break;
        }
    }

    if (get_IP.isEmpty()) {
        qWarning() << "IP-адрес не найден!";
    } else {
        qDebug() << "IP-адрес устройства:" << get_IP;
    }

    return get_IP;
}

connectDev::~connectDev()
{
    delete ui;
}
