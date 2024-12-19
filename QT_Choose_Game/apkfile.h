#ifndef APKFILE_H
#define APKFILE_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class apkfile;
}

class apkfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit apkfile(QWidget *parent = nullptr);
    ~apkfile();


private slots:
    void connect_command();

private:
    Ui::apkfile *ui;
};

#endif // APKFILE_H
