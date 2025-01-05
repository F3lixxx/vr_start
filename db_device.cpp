#include "db_device.h"

data_base::data_base(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::data_base)
{
    ui->setupUi(this);    
    addDevices = QSqlDatabase::addDatabase("QSQLITE");
    addDevices.setDatabaseName("ParseXML.db");

     if(!addDevices.open()){
        qDebug() << "Failed to open Data Base ParseXML: " << parse_db.lastError().text();
        qDebug() << "====================================================================\n";
    }else{
        QSqlQuery a_query;
         QString str_create = R"(
                "CREATE TABLE IF NOT EXISTS Devices ("
                 "Name VARCHAR(255) PRIMARY KEY NOT NULL,"
                 "IP INTEGER,"
                 "Port INTEGER);)";
}

data_base::~data_base(){
    addDevices.close();
}

bool data_base::insertIntoDB(const QString& Name, const QString IP, int port){
        QSqlQuery query;
           QString str_insert = "INSERT INTO Devices(Name, IP, Port) VALUES (:Name, :IP, :Port);";
            a_query.prepare(str_insert);
            a_query.bindValue(":Name", informationDev->devName());  // Привязываем значения
            a_query.bindValue(":IP", informationDev->getIP());
            a_query.bindValue(":Port", informationDev->set_port());

 if (!query.exec()) {
        qDebug() << "Failed to insert data into database:" << query.lastError().text();
        qDebug() << "====================================================================\n";
        return false;
    }

    qDebug() << "Data inserted successfully:" << Name << IP << port;
    qDebug() << "====================================================================\n";
    return true;
}

bool data_base::searchInfo(const QString& Name, const QString IP, int port){
    QProcess *devices = new QProcess(this);

    devices->setProgram(adb);
    devices->setArguments(QStringList() << "devices");

    QString command = adb + " " + devices->arguments().join(" ");
    qDebug() << "Executing command:" << command;

    connect (devices, &QProcess::readyReadStandardOutput, this, [this, devices](){
        QByteArray output = devices->readAllStandardOutput();
        ui->te_devices->append(QString::fromUtf8(output));
        qDebug() << "Devices:" << output;
        qDebug() << "================================================================================" << "\n";
    });

    connect (devices, &QProcess::readyReadStandardError, this, [this, devices](){
        QByteArray errorOutput = devices->readAllStandardError();
        ui->te_devices->append(QString::fromUtf8(errorOutput));
        qDebug() << "Errors:" << errorOutput;
        qDebug() << "================================================================================" << "\n";
    });

    devices->start();

    if(!devices->waitForFinished()){
        qDebug() << "Can't start ADB" << devices->errorString();
    }
    //новый процесс получения имени
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
        qDebug() << "================================================================================" << "\n";
    }else{
        qDebug() << outputStr;
        qDebug() << "================================================================================" << "\n";

    }
    deviceName = outputStr;

    //новый процесс назначения порта
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
    qDebug() << "================================================================================" << "\n";

    //новый процесс получения IP 
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
        qDebug() << "================================================================================" << "\n";
    } else {
        qDebug() << "IP-адрес устройства:" << get_IP;
        qDebug() << "================================================================================" << "\n";
    }

    return insertIntoDB(deviceName, get_IP, port);

}