#include "getdeviceip.h"

getIP::getIP(){
    QProcess process;

    process.start("adb", QStringList() << "shell" << "ip addr show wlan0");
    if (!process.waitForFinished()) {
        qWarning() << "Команда для получения IP-адреса не выполнена!";
        return;
    }

    QByteArray output = process.readAllStandardOutput();
    QString outputStr(output);

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

    process.start("adb", QStringList() << "shell" << "getprop" << "ro.product.model");
    if (!process.waitForFinished()) {
        qWarning() << "Команда для получения модели устройства не выполнена!";
        return;
    }

    output = process.readAllStandardOutput();
    outputStr = QString(output).trimmed();
    if (outputStr.isEmpty()) {
        qWarning() << "Модель устройства не найдена!";
    } else {
        nameDev = outputStr;
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
