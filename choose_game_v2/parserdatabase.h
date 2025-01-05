#ifndef PARSERDATABASE_H
#define PARSERDATABASE_H

#include <QDialog>

#include <QString>
#include <QXmlStreamReader>
#include <QDir>
#include <QDomDocument>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class ParserDataBase;
}

class ParserDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit ParserDataBase(QWidget *parent = nullptr);
    ~ParserDataBase();
    bool parseXml(const QString& filePath);
    bool parseFolder(const QString &folderPath);
    bool isFileProcessed(const QString& fileName);
    bool markFileAsProcessed(const QString& fileName);

private:
    Ui::ParserDataBase *ui;
    QSqlDatabase parse_db;
    bool insertIntoDB(const QString& packageName, const QString& activityName);
};

#endif // PARSERDATABASE_H
