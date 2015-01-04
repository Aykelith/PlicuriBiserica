#ifndef TABELFEREASTRA_H
#define TABELFEREASTRA_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QCloseEvent>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <fstream>
#include <vector>

#include "Database.hpp"
#include "Useful.hpp"

#include "AdaugareFereastra.hpp"

class TabelFereastra : public QDialog
{
    Q_OBJECT
public:
    explicit TabelFereastra(QSqlDatabase *db, QString data, bool editabil = false, QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void adaugare();
    void printeaza();
    void cauta();
    void adaugareTerminata(int result);
    void verificaInserator(QString text);
    void stergeRand();

private:
    void seteazaQuery(QString queryAditional);

private:
    QSqlDatabase *m_db;

    QVBoxLayout *m_layoutPrincipal;

    QHBoxLayout *m_layoutOptiuni;
    QPushButton *m_buttonAdauga;
    QPushButton *m_buttonPrinteaza;
    QPushButton *m_buttonInapoi;

    QHBoxLayout *m_layoutCauta;
    QLineEdit *m_lineEditCauta;
    QComboBox *m_comboBoxCauta;
    QPushButton *m_buttonCauta;


    QHBoxLayout *m_layoutInserator;
    QLabel *m_labelInserator;
    QLineEdit *m_lineEditInserator;

    QTableView *m_tabel;
    QSqlQueryModel *m_tabelModel;

    AdaugareFereastra *m_fereastraAdaugare;

    QString m_data;
    int m_seria;

    QString m_cautareInitiala;

    QString m_numeTabel;

    bool m_restrictionareData;

    std::vector<QPushButton*> m_buttonsSterge;

    bool m_printat;
    bool m_editabil;
};

#endif // TABELFEREASTRA_H
