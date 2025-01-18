#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbWin = new data_base;
    parserxml = new ParserDataBase;
    parse_db = QSqlDatabase::addDatabase("QSQLITE", "Parser");
    parse_db.setDatabaseName("ParseXML.db");
    if (!parse_db.open()) {
        qDebug() << "Не удалось открыть базу данных:" << parse_db.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных.");
        return;
    }
    model = new QSqlTableModel(this, parse_db);
    qDebug() << "Available drivers in Device DB:" << QSqlDatabase::drivers();

    model->setTable("ManifestData");
    model->select();
    ui->tv_deviceDB->reset();
    if (!model->select()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные из таблицы.Parser из MainWindow");
        return;
    }
    ui->tv_deviceDB->setModel(model);

}



void MainWindow::on_pb_openDB_clicked()
{
    dbWin->show();
}

void MainWindow::on_pb_openDBxml_clicked()
{
}

void MainWindow::on_tv_deviceDB_clicked(const QModelIndex &index)
{
    // Получаем индекс выбранной строки
    currentRow = index.row();
    ui->tv_deviceDB->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите устройство из списка.");
        return;
    }
    dbWin->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
