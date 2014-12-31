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
