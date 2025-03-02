#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QDialog>
#include <QDebug>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>
#include <QSqlError>
#include <QDir>
#include <QSqlTableModel>
#include <QDebug>

#include "connectdev.h"
#include "apk_window.h"

namespace Ui {
class data_base;
}

class data_base : public QDialog
{
    Q_OBJECT

public:
    explicit data_base(QWidget *parent = nullptr, const QString& db);
    ~data_base();

//работа с Базой данных
    void create_DB();
    void show_DB();
    void connect_wifi(QString ipAddress);
//конец создания БД

    bool searchInfo();

private slots:

    void on_tv_db_clicked(const QModelIndex &index);

    void on_pb_delete_clicked();

private:
    Ui::data_base *ui;
    QString adb = "cd /../../platform-tools/adb.exe";
    connectDev *informationDev;
    apk_window *apkStart;
    QSqlDatabase addDevices;
    QSqlTableModel *model;
    int currentRow;
    int currentColumn;

    bool insertIntoDB(const QString& Name, const QString IP, int port);
};

#endif // DATA_BASE_H
