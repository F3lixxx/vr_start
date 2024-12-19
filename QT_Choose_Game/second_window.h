#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include "apkfile.h"
#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QProcess>


namespace Ui {
class second_window;
}

class second_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit second_window(QWidget *parent = nullptr);
    ~second_window();
    void open_window_apk();

private slots:
    void executeCommand();

private:
    Ui::second_window *ui;
    apkfile *apk;
};

#endif // SECOND_WINDOW_H
