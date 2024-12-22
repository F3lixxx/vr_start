#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <QByteArray>
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
//PushButton start
    void window_install_device();
    void window_choose_game();
//end

//add database
    void data_base();
//

    void connected_devices();
    void readOutput();
    void readError();

private:
    Ui::MainWindow *ui;
    second_window* sec_win;
    add_new_devices* add_device;
};
#endif // MAINWINDOW_H
