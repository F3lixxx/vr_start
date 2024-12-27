#include "data_base.h"
#include "ui_data_base.h"

data_base::data_base(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::data_base)
{
    ui->setupUi(this);
    informationDev = new connectDev;
    apkStart = new apk_window;
}

void data_base::create_DB(){
    addDevices = QSqlDatabase::addDatabase("QSQLITE");

    addDevices.setDatabaseName("device_table.db");

    if(!addDevices.open()){
        qDebug() << addDevices.lastError().text();
        return;
    }

    QSqlQuery a_query;

    // Создаем таблицу, если она не существует
    QString str_create = "CREATE TABLE IF NOT EXISTS Devices ("
                         "Name VARCHAR(255) PRIMARY KEY NOT NULL,"
                         "IP INTEGER,"
                         "Port INTEGER);";
    bool b = a_query.exec(str_create);

    if (!b) {
        qDebug() << "Table creation failed!" << a_query.lastError().text();
        return;
    }

    QString deviceName = informationDev->devName();
    if (deviceName.isEmpty()) {
        qWarning() << "Device name is empty. Cannot insert into database.";
        return; // Прерываем выполнение, если имя устройства пустое
    }

    // Вставляем данные в таблицу Devices
    QString str_insert = "INSERT INTO Devices(Name, IP, Port) VALUES (:Name, :IP, :Port);";
    a_query.prepare(str_insert);
    a_query.bindValue(":Name", informationDev->devName());  // Привязываем значения
    a_query.bindValue(":IP", informationDev->getIP());
    a_query.bindValue(":Port", informationDev->set_port());

    b = a_query.exec();
    if (!b) {
        qDebug() << "Insert failed!" << a_query.lastError().text();
        return;
    }

    qDebug() << "Device added successfully!";
    QSqlRecord rec = a_query.record();
    addDevices.close();
}

void data_base::show_DB(){
    model = new QSqlTableModel(this, addDevices);
    model->setTable("Devices");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tv_db->setModel(model);
}

data_base::~data_base()
{
    delete ui;
}

void data_base::connect_wifi(QString ipAddress){

    QProcess *wifi_connect = new QProcess(this);

    wifi_connect->setProgram(adb);
    QStringList arguments = QStringList() << "connect" << ipAddress + ":5555 shell";
    wifi_connect->setArguments(arguments);

    // Составляем строку команды для вывода в qDebug
    QString command = adb + " " + arguments.join(" ");
    qDebug() << "Executing command:" << command;

    wifi_connect->start();

    if(!wifi_connect->waitForFinished()){
        qDebug() << "Can't connect from wifi ADB!" << wifi_connect->errorString();
    }else{
        qDebug() << "ADB connected to wifi successfully!";
    }

    QProcess *connect_dev = new QProcess(this);

    connect_dev->setProgram(adb);
    QStringList arguments_connectDev = QStringList() << "-s" << ipAddress + ":5555 shell";
    wifi_connect->setArguments(arguments);

    // Составляем строку команды для вывода в qDebug
    QString commandConnectDev = adb + " " + arguments_connectDev.join(" ");
    qDebug() << "Executing command:" << commandConnectDev;

    connect_dev->start();

    if(!connect_dev->waitForFinished()){
        qDebug() << "Can't connect select device!" << connect_dev->errorString();
    }else{
        qDebug() << "ADB connected selected device successfully!";
    }
}

// void data_base::on_pb_connect_clicked()
// {
//     model->select();
// }

void data_base::on_pb_delete_clicked()
{
    model->removeRow(currentRow);
    model->submitAll();
    model->select();
}

void data_base::on_tv_db_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    currentColumn = index.column();

    // Извлекаем IP-адрес из выбранной строки
    QModelIndex ipIndex = model->index(currentRow, 1);  // 1 - это индекс столбца IP
    QString ipAddress = model->data(ipIndex).toString();

    qDebug() << "Selected IP Address: " << ipAddress;
    connect_wifi(ipAddress);  // Пример использования IP-адреса для подключения
    apkStart->show();

    QProcess *wifi_connect = new QProcess(this);

    wifi_connect->setProgram(adb);
    QStringList arguments = QStringList() << "devices";
    wifi_connect->setArguments(arguments);

    // Составляем строку команды для вывода в qDebug
    QString command = adb + " " + arguments.join(" ");
    qDebug() << "Executing command:" << command;
}

