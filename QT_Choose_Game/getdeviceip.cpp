#include "getdeviceip.h"

getIP::getIP(){
    QProcess process;
    process.start("adb", QStringList() << "shell" << "ip addr show wlan0");
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QString outputStr(output);
    // qDebug() << "Output from command:" << outputStr;

    // Разделяем вывод по строкам
    QStringList lines = outputStr.split('\n');

    // Ищем строку, содержащую IP-адрес для wlan0
    for (const QString &line : lines) {
        if (line.contains("inet ")) {
            QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            // Второй элемент — это IP-адрес, маска подсети игнорируется
            ip = parts[1].split('/')[0];  // Возвращаем только IP-адрес
            break;
        }
    }

    portDev = 5555;
}

QString getIP::getName() const {
    return nameDev;
}

QString getIP::getip() const{
    return ip;
}

int getIP::port() const {
    return portDev;
}
