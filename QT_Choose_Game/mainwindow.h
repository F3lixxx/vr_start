#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <QByteArray>
#include <QSqlTableModel>

#include "second_window.h"
#include "add_new_devices.h"

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

    void connected_devices();
    void readOutput();
    void readError();


private:
    Ui::MainWindow *ui;
    second_window* sec_win;
    add_new_devices* add_device;
    QSqlTableModel* model;
};
#endif // MAINWINDOW_H
