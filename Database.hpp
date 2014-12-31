#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QSqlDatabase>
#include <QSqlError>

#include <QApplication>

#include <QFileDialog>
#include <QMessageBox>

#include <fstream>

#include "Global.hpp"

static QString db_databasePath;

inline void loadDatabasePath()
{
    std::ifstream file("data/DatabasePath.xaldata");
    if (file.good()) qDebug() << "IS GOOD!"; else qDebug() << "NOT IS GOOD!";
    std::string path;
    file >> path;
    qDebug() << QString::fromStdString(path);
    db_databasePath = QString::fromStdString(path);
}

inline void saveDatabasePath()
{
    std::ofstream file("data/DatabasePath.xaldata");
    if (file.good()) qDebug() << "IS GOOD!"; else qDebug() << "NOT IS GOOD!";
    file << db_databasePath.toStdString();
}

inline void getDatabasePath()
{
    QMessageBox errorMessageBox(QMessageBox::Critical, "Eroare baza de date", "Baza de date nu a fost gasita. Click pe buton pentru a selecta pozitia bazei de date", QMessageBox::Ok);
    if (errorMessageBox.exec() == QMessageBox::Ok)
    {
        db_databasePath = QFileDialog::getOpenFileName(0, "Select database", "", "Database Files (*.sqlite)");
        saveDatabasePath();
    }
}

inline bool connectDatabase(QSqlDatabase &db, bool lastTry = false)
{
    bool result = false;
    if (db_databasePath == "") loadDatabasePath();
    if (db_databasePath != "" && db_databasePath != "null")
    {
        db.setDatabaseName(db_databasePath);
        result = db.open();
    }

    if (result)
        return true;
    else
    {
        if (db.lastError().driverText() == "Driver not loaded")
        {
            db = QSqlDatabase::addDatabase("QSQLITE");
            return connectDatabase(db);
        }
        if (lastTry)
            return false;
        getDatabasePath();
        return connectDatabase(db, true);
    }
}

#endif // DATABASE_HPP

