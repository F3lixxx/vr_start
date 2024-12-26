#include "data_base.h"
#include "ui_data_base.h"

data_base::data_base(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::data_base)
{
    ui->setupUi(this);
    informationDev = new connectDev;
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

void data_base::on_pb_connect_clicked()
{
    model->selectRow(currentRow);
    model->submitAll();
    informationDev->connect_wifi();
    model->select();
}

void data_base::on_pb_delete_clicked()
{
    model->removeRow(currentRow);
    model->submitAll();
    model->select();
}

void data_base::on_tv_db_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

