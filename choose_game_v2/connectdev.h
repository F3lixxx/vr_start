#ifndef CONNECTDEV_H
#define CONNECTDEV_H

#include <QDialog>
#include <cstdlib>
#include <QByteArray>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


namespace Ui {
class connectDev;
}

class connectDev : public QDialog
{
    Q_OBJECT

public:
    explicit connectDev(QWidget *parent = nullptr);
    ~connectDev();

    void connected_dev();
    void connect_wifi();
    bool isConnected();
    QString devName();
    QString getIP();
    int set_port();
    bool isDeviceConnected(const QString& ipAddress);

private:
    Ui::connectDev *ui;
    QString adb = "cd /../../platform-tools/adb.exe";
    QString deviceName;
    QString get_IP;
    int port = 5555;

};

#endif // CONNECTDEV_H
