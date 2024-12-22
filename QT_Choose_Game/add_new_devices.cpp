#include "add_new_devices.h"
#include "ui_add_new_devices.h"

add_new_devices::add_new_devices(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::add_new_devices)
{
    ui->setupUi(this);
    connect(ui->pb_add_device, &QPushButton::clicked, this, &add_new_devices::add_dev);
}


void add_new_devices::add_device(const QString &name, int ip, int port){
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");

    sdb.setDatabaseName("device_table.sqlite");

    qDebug() << "Current Path to Data Base: " << QDir::currentPath();

    if(!sdb.open()){
        qDebug() << sdb.lastError().text();
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

    // Вставляем данные в таблицу Devices
    QString str_insert = "INSERT INTO Devices(Name, IP, Port) VALUES (:Name, :IP, :Port);";
    a_query.prepare(str_insert);
    a_query.bindValue(":Name", name);  // Привязываем значения
    a_query.bindValue(":IP", ip);
    a_query.bindValue(":Port", port);

    b = a_query.exec();
    if (!b) {
        qDebug() << "Insert failed!" << a_query.lastError().text();
        return;
    }

    qDebug() << "Device added successfully!";
    QSqlRecord rec = a_query.record();
}

void add_new_devices::add_dev(){
    QString dev_name = ui->le_name->text();
    int IP = ui->le_IP->text().toInt();
    int Port = ui->le_port->text().toInt();

    add_device(dev_name, IP, Port);
}

add_new_devices::~add_new_devices()
{
    delete ui;
}
