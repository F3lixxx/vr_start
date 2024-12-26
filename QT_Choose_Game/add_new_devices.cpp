#include "add_new_devices.h"
#include "ui_add_new_devices.h"
#include "getdeviceip.h"

add_new_devices::add_new_devices(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::add_new_devices)
{
    ui->setupUi(this);
    this->setWindowTitle("Device data base");
}

void add_new_devices::add_dev() {
    getIP device; // Создаем объект getIP, который автоматически заполнит данные
    add_device(device); // Передаем объект в метод добавления
}

void add_new_devices::add_device(const getIP& device){

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

    // Вставляем данные в таблицу Devices
    QString str_insert = "INSERT INTO Devices(Name, IP, Port) VALUES (:Name, :IP, :Port);";
    a_query.prepare(str_insert);
    a_query.bindValue(":Name", device.getName());  // Привязываем значения
    a_query.bindValue(":IP", device.getip());
    a_query.bindValue(":Port", device.port());

    b = a_query.exec();
    if (!b) {
        qDebug() << "Insert failed!" << a_query.lastError().text();
        return;
    }

    qDebug() << "Device added successfully!";
    QSqlRecord rec = a_query.record();

    model = new QSqlTableModel(this, addDevices);
    model->setTable("Devices");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tv_Data_base->setModel(model);

    addDevices.close();
}

add_new_devices::~add_new_devices()
{
    delete ui;
}
