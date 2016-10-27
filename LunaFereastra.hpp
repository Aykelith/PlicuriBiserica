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

#ifndef LUNAFEREASTRA_H
#define LUNAFEREASTRA_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QCloseEvent>
#include <QInputDialog>
#include <QDate>

#include "Database.hpp"
#include "Useful.hpp"

class SelectareLunaFereastra;
class TabelFereastra;

class LunaFereastra : public QWidget
{
    Q_OBJECT
public:
    explicit LunaFereastra(QString data, QSqlDatabase *db, QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void ziNoua();
    void vizualizare();

private:


private:
    QSqlDatabase *m_db;

    QVBoxLayout *m_layoutPrincipal;

    QPushButton *m_buttonZiNoua;
    QPushButton *m_buttonVizualizare;
    QPushButton *m_buttonStatut;
    QPushButton *m_buttonInapoi;

    SelectareLunaFereastra *m_fereastraSelectareLuna;
    TabelFereastra *m_fereastraTabel;

    QString m_data;
};

#endif // LUNAFEREASTRA_H
