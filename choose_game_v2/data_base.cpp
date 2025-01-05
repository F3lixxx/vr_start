#include "data_base.h"
#include "ui_data_base.h"

data_base::data_base(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::data_base)
{
    ui->setupUi(this);
    apkStart = new apk_window;

    addDevices = QSqlDatabase::addDatabase("QSQLITE", "Devices");
    addDevices.setDatabaseName("Device.db");
    qDebug() << "Available drivers in Device DB:" << QSqlDatabase::drivers();

    if(!addDevices.open()){
        qDebug() << "Failed to open Data Base Devices: " << addDevices.lastError().text();
        qDebug() << "====================================================================\n";
        return;
    }
        QSqlQuery a_query(QSqlDatabase::database("Devices"));
        QString str_create = "CREATE TABLE IF NOT EXISTS Devices ("
            "Name TEXT PRIMARY KEY NOT NULL,"
            "IP TEXT,"
            "Port INTEGER);";
        if (!a_query.exec(str_create)) {
            qDebug() << "Failed to fetch table info:" << a_query.lastError().text();
            return;
        }
        QStringList tables = addDevices.tables();
        qDebug() << "Существующие таблицы в базе данных:" << tables;
    }


bool data_base::searchInfo(){
    QString deviceName;
    QString IP;
    int port = 5555;
    QProcess *devices = new QProcess(this);

    devices->setProgram(adb);
    devices->setArguments(QStringList() << "devices");

    QString command = adb + " " + devices->arguments().join(" ");
    qDebug() << "Executing command:" << command;

    connect (devices, &QProcess::readyReadStandardOutput, this, [this, devices](){
        QByteArray output = devices->readAllStandardOutput();
        qDebug() << "Devices:" << output;
        qDebug() << "================================================================================" << "\n";
    });

    connect (devices, &QProcess::readyReadStandardError, this, [this, devices](){
        QByteArray errorOutput = devices->readAllStandardError();
        qDebug() << "Errors:" << errorOutput;
        qDebug() << "================================================================================" << "\n";
    });

    devices->start();

    if(!devices->waitForFinished()){
        qDebug() << "Can't start ADB" << devices->errorString();
    }

    //процесс получения имени
    QProcess *devicesName = new QProcess(this);
    devicesName->setProgram(adb);
    devicesName->setArguments(QStringList() << "shell" << "getprop" << "ro.product.model");
    QString error = "can't get name";
    // Составляем строку команды для вывода в qDebug
    command = adb + " " + devicesName->arguments().join(" ");
    qDebug() << "Executing command:" << command;

    devicesName->start();
    if(!devicesName->waitForFinished()){
        qDebug() << "Can't start command adb shell getprop ro.product.model" << devices->errorString();
        return false;
    }else{
        qDebug() << "ADB start command: adb shell getprop ro.product.model!";
    }

    QString outputStrName = QString::fromUtf8(devicesName->readAllStandardOutput()).trimmed();
    if (outputStrName.isEmpty()) {
        qWarning() << "Модель устройства не найдена!";
        qDebug() << "================================================================================" << "\n";
    }else{
        qDebug() << outputStrName;
        qDebug() << "================================================================================" << "\n";

    }
    deviceName = outputStrName;

    //новый процесс получения IP
    QProcess process_get_IP(this);

    process_get_IP.setProgram(adb);
    QStringList arguments = QStringList() << "shell" << "ip" << "addr" << "show" << "wlan0";
    process_get_IP.setArguments(arguments);

    command = adb + " " + process_get_IP.arguments().join(" ");
    qDebug() << "Executing command:" << command;
    process_get_IP.start();

    if (!process_get_IP.waitForFinished()) {
        qWarning() << "Не удалось получить IP-адрес!";
    }else{
        qDebug() << "ADB start command: adb shell ip addr show wlan0!";
    }

    QString outputStrIP = QString::fromUtf8(process_get_IP.readAllStandardOutput());
    QStringList lines = outputStrIP.split('\n');

    for (const QString &line : lines) {
        if (line.contains("inet ")) {
            QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            IP = parts[1].split('/')[0];
            break;
        }
    }

    if (IP.isEmpty()) {
        qWarning() << "IP-адрес не найден!";
        qDebug() << "================================================================================" << "\n";
    } else {
        qDebug() << "IP-адрес устройства:" << IP;
        qDebug() << "================================================================================" << "\n";
    }

    // новый процесс назначения порта
    QProcess set_port(this);

    set_port.setProgram(adb);
    set_port.setArguments(QStringList() << "tcpip" << "5555");

    set_port.start();
    if(!set_port.waitForFinished()){
        qDebug() << "Can't start command adb tcpip 5555" << set_port.errorString();
        return -1;
    }else{
        qDebug() << "ADB start: command adb tcpip 5555!";
    }

    port = 5555;
    qDebug() << "Port устройства:" << port;
    qDebug() << "================================================================================" << "\n";

    return insertInfoDB(deviceName, IP, port);
}

bool data_base::insertInfoDB(const QString& Name, const QString IP, int port){
    QSqlQuery a_query(QSqlDatabase::database("Devices"));

    if (!addDevices.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
    //Проверка на существование записи
    QString check_query = "SELECT COUNT(*) FROM Devices WHERE Name = :Name AND IP = :IP AND Port = :Port;";
    a_query.prepare(check_query);
    a_query.bindValue(":Name", Name);  // Привязываем значения
    a_query.bindValue(":IP", IP);
    a_query.bindValue(":Port", port);

    if(!a_query.exec()){
        qWarning() << "Check query failed!!!" << a_query.lastError().text();
        return false;
    }

    a_query.next();
    int count = a_query.value(0).toInt();

    if(count > 0){
        qDebug() << "Record is alredy exists. Skip insert";
        return false;
    }


    QString str_insert = "INSERT INTO Devices(Name, IP, Port) VALUES (:Name, :IP, :Port);";

    a_query.prepare(str_insert);
    a_query.bindValue(":Name", Name);
    a_query.bindValue(":IP", IP);
    a_query.bindValue(":Port", port);

    if (!a_query.exec()) {
        qDebug() << "Ошибка вставки данных в таблицу:" << a_query.lastError().text();
        return false;
    }

    qDebug() << "Данные успешно добавлены в таблицу 'Devices'." << Name << IP << port;

    if (!a_query.isActive()) {
        qDebug() << "Query is not active:" << a_query.lastError().text();
        return false;
    }

    if (addDevices.isOpen()) {
        addDevices.close();
        qDebug() << "Device Data Base closed";
    }

    return true;
}

data_base::~data_base(){
    QSqlDatabase::removeDatabase("Devices");
}
