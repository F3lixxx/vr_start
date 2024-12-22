#include "database.h"

void DB_devices::add_new_device(){
    QSqlQuery a_query;
    QString str =   "CREATE TABLE IF NOT EXISTS Devices ("
                  "name VARCHAR(255) PRIMARY KEY NOT NULL,"
                  "IP integer, "
                  "Port integer"
                  ");";
    bool b = a_query.exec(str);
    if(!b){
        qDebug() << "Table is not create!" << a_query.lastError().text();
        return;
    }

    QString str_insert = "INSERT INTO ID(Name, IP, Port)"
                         "VALUES (:Name, :IP, :Port);";
    a_query.prepare(str_insert);
    a_query.bindValue(":Name", 14);      // Привязываем значения
    a_query.bindValue(":IP", "michigan");
    a_query.bindValue(":Port", 25);
    b = a_query.exec(str);

    if(!b){
        qDebug() << "Cannot insert values! Error:" << a_query.lastError().text();
        return;
    }

    if (!a_query.exec("SELECT number, address, age FROM ID")) {
        qDebug() << "Error retrieving data! Error:" << a_query.lastError().text();
        return;
    }

    QSqlRecord rec = a_query.record();
    int number = 0;
    int age = 0;
    QString address = "";

    while (a_query.next()) {
        number = a_query.value(rec.indexOf("number")).toInt();
        age = a_query.value(rec.indexOf("age")).toInt();
        address = a_query.value(rec.indexOf("address")).toString();

        qDebug() << "number is " << number
                 << ". age is " << age
                 << ". address" << address;
    }
}
