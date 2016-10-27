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

#ifndef SELECTARELUNAFEREASTRA_HPP
#define SELECTARELUNAFEREASTRA_HPP

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>

#include "Database.hpp"
#include "Useful.hpp"
#include "Global.hpp"

#include "TabelFereastra.hpp"

class LunaFereastra;

class SelectareLunaFereastra : public QWidget
{
    Q_OBJECT

public:
    SelectareLunaFereastra(QSqlDatabase *db, QWidget *parent = 0);

private slots:
    void vizualizareLuna();
    void vizualizareAn();
    void vizualizareMembrii();
    void construiesteLunile(QString anul);

private:
    void verificAnNou();
    void construiesteAnii();
    QString getMonth(int number);

private:
    QSqlDatabase *m_db;

    QVBoxLayout *m_layoutPrincipal;

    QComboBox *m_comboBoxAn;
    QComboBox *m_comboBoxLuna;

    QPushButton *m_buttonVizualizareLuna;
    QPushButton *m_buttonVizualizareAn;
    QPushButton *m_buttonMembrii;
    QPushButton *m_buttonIesire;

    LunaFereastra *m_fereastraLuna;
    TabelFereastra *m_fereastraTabel;
};

#endif // SELECTARELUNAFEREASTRA_HPP
