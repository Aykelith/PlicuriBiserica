////////////////////////////////////////////////////////////////////////////////
//    PlicuriBiserica
//    Copyright (C) 2014-2016 Prisacariu Alexandru
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////

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
