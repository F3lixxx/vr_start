#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

// #include "connectdev.h"
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
    // void on_pb_check_dev_clicked();

    void on_pb_openDB_clicked();

    void on_pb_openDBxml_clicked();

private:
    Ui::MainWindow *ui;
    // connectDev *winConDev;
    data_base *dbWin;
    ParserDataBase *parserxml;
};
#endif // MAINWINDOW_H
