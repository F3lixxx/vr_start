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
#include <QMessageBox>

#include "connectdev.h"
#include "apk_window.h"
#include "parserdatabase.h"

namespace Ui {
class data_base;
}

class data_base : public QDialog
{
    Q_OBJECT

public:
    explicit data_base(QWidget *parent = nullptr);
    ~data_base();

    bool searchInfo();

private slots:

    void on_pb_delete_clicked();

    void on_tv_db_clicked(const QModelIndex &index);

    void on_pb_connect_clicked();

private:
    Ui::data_base *ui;
    QString adb = "cd /../../platform-tools/adb.exe";
    connectDev *informationDev;
    apk_window *apkStart;
    QSqlDatabase addDevices;
    QSqlTableModel *model;
    int currentRow;
    int currentColumn;
    ParserDataBase *parse;

    bool insertInfoDB(const QString& Name, const QString IP, int port);
};

#endif // DATA_BASE_H
