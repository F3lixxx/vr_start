#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QProcess>
#include <QTextStream>
#include <QString>
#include <QRegularExpression>
#include <QDebug>

QString getDeviceIp() {
    QProcess process;
    process.start("adb", QStringList() << "shell" << "ip addr show wlan0");
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QString outputStr(output);

    // Разделяем вывод по строкам
    QStringList lines = outputStr.split('\n');

    // Ищем строку, содержащую IP-адрес для wlan0
    for (const QString &line : lines) {
        if (line.contains("inet ")) {
            QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            // Второй элемент — это IP-адрес, маска подсети игнорируется
            return parts[1].split('/')[0];  // Возвращаем только IP-адрес
        }
    }

    return QString("IP не найден");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString ip = getDeviceIp();
    qDebug() << "IP-адрес устройства: " << ip;
    w.show();
    return a.exec();
}
