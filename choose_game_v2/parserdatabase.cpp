#include "parserdatabase.h"
#include "ui_parserdatabase.h"

ParserDataBase::ParserDataBase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ParserDataBase)
{
    ui->setupUi(this);

    parse_db = QSqlDatabase::addDatabase("QSQLITE", "Parser");
    parse_db.setDatabaseName("ParseXML.db");
    qDebug() << "Available drivers in Parser DB:" << QSqlDatabase::drivers();
    modelParser = new QSqlTableModel(this, parse_db);

    modelParser->select();


    if(!parse_db.open()){
        qDebug() << "Failed to open Data Base ParseXML: " << parse_db.lastError().text();
        qDebug() << "====================================================================\n";
        return;
    }else{
        QSqlQuery query(QSqlDatabase::database("Parser"));
        QString createTable = R"(
            CREATE TABLE IF NOT EXISTS ManifestData (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                packageName TEXT NOT NULL,
                activityName TEXT NOT NULL
            );
        )";

        if(!query.exec(createTable)){
            qDebug() << "Failed create table in parser" << parse_db.lastError().text();
            qDebug() << "====================================================================\n";
        }

        QString createProcessedFilesTable = R"(
        CREATE TABLE IF NOT EXISTS ProcessedFiles (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            fileName TEXT NOT NULL UNIQUE
        );
    )";

        if (!query.exec(createProcessedFilesTable)) {
            qDebug() << "Failed to create table ProcessedFiles:" << query.lastError().text();
            qDebug() << "====================================================================\n";
        }
    }

    modelParser->setTable("ManifestData");
    modelParser->select();
    if (!modelParser->select()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные из таблицы.Parser");
        return;
    }
    ui->tv_dataBase->setModel(modelParser);
}

bool ParserDataBase::parseXml(const QString& filePath){
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Can't open file" << filePath;
        qDebug() << "====================================================================\n";
        return false;
    }

    QDomDocument doc;
    if(!doc.setContent(&file)){
        qDebug() << "Failed to parse XML content";
        qDebug() << "====================================================================\n";
        file.close();
        return false;
    }
    file.close();

    QDomElement manifestElement = doc.documentElement();
    QString packageName = manifestElement.attribute("package");

    QDomNodeList activityNodes = manifestElement.elementsByTagName("activity");
    QString activityName;

    for(int i = 0; i < activityNodes.count(); ++i){
        QDomElement activityElement = activityNodes.at(i).toElement();
        if(activityElement.hasAttribute("android:name")){
            activityName = activityElement.attribute("android:name");
            break;
        }
    }

    if(packageName.isEmpty() || activityName.isEmpty()){
        qDebug() << "Required attributes not found in XML file!";
        return false;
    }

    modelParser->select();
    return insertIntoDB(packageName, activityName);
}


bool ParserDataBase::insertIntoDB(const QString& packageName, const QString& activityName){
    QSqlQuery query(QSqlDatabase::database("Parser"));

    query.prepare("INSERT INTO ManifestData (packageName, activityName) VALUES (:packageName, :activityName)");
    query.bindValue(":packageName", packageName);
    query.bindValue(":activityName", activityName);

    if (!query.exec()) {
        qDebug() << "Failed to insert data into database:" << query.lastError().text();
        qDebug() << "====================================================================\n";
        return false;
    }

    qDebug() << "Data inserted successfully:" << packageName << activityName;
    qDebug() << "====================================================================\n";
    return true;
}

bool ParserDataBase::parseFolder(const QString &folderPath){
    QDir dir(folderPath);
    if(!dir.exists()){
        qDebug() << "Directory does not exist: " << folderPath;
        qDebug() << "====================================================================\n";
        return false;
    }

    QStringList xmlFiles = dir.entryList(QStringList() << "*.xml", QDir::Files);
    if(xmlFiles.isEmpty()){
        qDebug() << "No XML files found in directory:" << folderPath;
        qDebug() << "====================================================================\n";
        return true;
    }

    foreach(const QString fileName, xmlFiles){
        QString filePath = dir.absoluteFilePath(fileName);

        if(isFileProcessed(fileName)){
            qDebug() << "File alredy processed, skipping: " << fileName;
            qDebug() << "====================================================================";
            continue;
        }

        if(parseXml(filePath)){
            markFileAsProcessed(fileName);
        }else{
            qDebug() << "Failed to process file:" << fileName;
            qDebug() << "====================================================================\n";
        }
    }
    return true;
}

bool ParserDataBase::isFileProcessed(const QString& fileName){
    QSqlQuery query(QSqlDatabase::database("Parser"));
    query.prepare("SELECT COUNT(*) FROM ProcessedFiles WHERE fileName = :fileName");
    query.bindValue(":fileName", fileName);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to check processed file:" << query.lastError().text();
        qDebug() << "====================================================================\n";
        return false;
    }

    return query.value(0).toInt() > 0;
}

bool ParserDataBase::markFileAsProcessed(const QString& fileName) {
    QSqlQuery query(QSqlDatabase::database("Parser"));
    query.prepare("INSERT INTO ProcessedFiles (fileName) VALUES (:fileName)");
    query.bindValue(":fileName", fileName);

    if (!query.exec()) {
        qDebug() << "Failed to mark file as processed:" << query.lastError().text();
        qDebug() << "====================================================================\n";
        return false;
    }

    if(!parse_db.isOpen()){
        parse_db.close();
        qDebug() << "ParseXML DB closed!";
    }
    return true;
}

bool ParserDataBase::startActivity(){
    QSqlQuery query(QSqlDatabase::database("Parser"));

    query.prepare("SELECT COUNT(*) FROM ManifestData WHERE packageName = :packageName AND activityName = :activityName)");
    // query.bindValue(":packageName", packageName);
    // query.bindValue(":activityName", activityName);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return false; // Обработка ошибки
    }

    QProcess *devices = new QProcess(this);

    devices->setProgram(adb);
    devices->setArguments(QStringList() << "shell am start -n" + packageName + activityName);

    QString command = adb + " " + devices->arguments().join(" ");
    qDebug() << "Executing command:" << command;

    connect (devices, &QProcess::readyReadStandardOutput, this, [this, devices](){
        QByteArray output = devices->readAllStandardOutput();
        qDebug() << "Devices:" << output;
        qDebug() << "================================================================================" << "\n";
    });

    connect (devices, &QProcess::readyReadStandardError, this, [this, devices](){
        QByteArray errorOutput = devices->readAllStandardError();
        qDebug() << "Errors:" << errorOutput;
        qDebug() << "================================================================================" << "\n";
    });

    devices->start();

    if(!devices->waitForFinished()){
        qDebug() << "Can't start ADB" << devices->errorString();
    }
    return true;
}

ParserDataBase::~ParserDataBase()
{
    QSqlDatabase::removeDatabase("Parser");
    delete ui;
}
