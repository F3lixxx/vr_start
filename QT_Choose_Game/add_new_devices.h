#ifndef ADD_NEW_DEVICES_H
#define ADD_NEW_DEVICES_H
#pragma once

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>
#include <QSqlError>
#include <QDir>
#include <QDebug>
#include "getdeviceip.h"

namespace Ui {
class add_new_devices;
}

class add_new_devices : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_new_devices(QWidget *parent = nullptr);
    ~add_new_devices();

    void add_dev();
    void add_device(const getIP& getip);
    void choose_device();

private:
    Ui::add_new_devices *ui;
    QSqlDatabase addDevices;
};

#endif // ADD_NEW_DEVICES_H
