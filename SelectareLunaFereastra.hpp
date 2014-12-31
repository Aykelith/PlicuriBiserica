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

class LunaFereastra;

class SelectareLunaFereastra : public QWidget
{
    Q_OBJECT

public:
    SelectareLunaFereastra(QSqlDatabase *db, QWidget *parent = 0);

private slots:
    void vizualizareLuna();
    //void vizualizareAn();
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
    QPushButton *m_buttonIesire;

    LunaFereastra *m_fereastraLuna;
};

#endif // SELECTARELUNAFEREASTRA_HPP
