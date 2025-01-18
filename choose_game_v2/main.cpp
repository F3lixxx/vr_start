#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

QFile logFile;

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    QString logMessage;
    QString currentTime = QDateTime::currentDateTime().toString("DD-MM-yyyy HH:mm:ss");

    switch(type) {
    case QtDebugMsg:
        logMessage = QString("[%1] Debug: %2").arg(currentTime, msg);
   case QtInfoMsg:
        logMessage = QString("[%1] Info: %2").arg(currentTime, msg);
        break;
    case QtWarningMsg:
        logMessage = QString("[%1] Warning: %2").arg(currentTime, msg);
        break;
    case QtCriticalMsg:
        logMessage = QString("[%1] Critical: %2").arg(currentTime, msg);
        break;
    case QtFatalMsg:
        logMessage = QString("[%1] Fatal: %2").arg(currentTime, msg);
        abort(); // Останавливает программу в случае фатальной ошибки
    }

    QTextStream out(&logFile);
    out << logMessage << Qt::endl;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logFile.setFileName("logs.ini");
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        qWarning() << "Can't open File at:" << QFileInfo(logFile).absoluteFilePath();
    }
    qInstallMessageHandler(customMessageHandler);

    MainWindow w;

    QString parsexml = "C:\\Users\\User\\Documents\\QT_Projects\\vr_start\\choose_game_v2\\apkFiles";
    ParserDataBase parse;
    if(parse.parseFolder(parsexml)){
        qDebug() << "XML parsed and data stored successfully.\n";
    }else{
        qDebug() << "Failed to parse XML or store data.\n";
    }

    data_base base;
    base.searchInfo();

    w.show();
    return a.exec();
}
