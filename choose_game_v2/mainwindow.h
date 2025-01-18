#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QSqlTableModel>

#include "data_base.h"
#include "parserdatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_openDB_clicked();

    void on_pb_openDBxml_clicked();

    void on_tv_deviceDB_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlDatabase parse_db;
    data_base *dbWin;
    ParserDataBase *parserxml;

    int currentRow;
    int currentColumn;
};
#endif // MAINWINDOW_H
