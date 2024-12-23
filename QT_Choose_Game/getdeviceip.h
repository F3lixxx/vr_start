#ifndef GETDEVICEIP_H
#define GETDEVICEIP_H
#pragma once
#include <QCoreApplication>
#include <QProcess>
#include <QTextStream>
#include <QString>
#include <QRegularExpression>
#include <QDebug>

class getIP{
public:
    getIP();
    QString getName() const;
    QString getip() const;
    int port() const;

private:
    QString nameDev = "Xiaomi";
    QString ip;
    int portDev;
};

#endif // GETDEVICEIP_H
