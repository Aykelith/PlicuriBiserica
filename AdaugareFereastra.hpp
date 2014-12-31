#ifndef ADAUGAREFEREASTRA_H
#define ADAUGAREFEREASTRA_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QSqlQuery>
#include <QSqlDatabase>

#include <vector>
#include <utility>

#include "Database.hpp"
#include "Useful.hpp"

class AdaugareFereastra : public QDialog
{
    Q_OBJECT
public:
    explicit AdaugareFereastra(QString data, QString inserator, int seria, QSqlDatabase *db, QWidget *parent = 0);

signals:

private slots:
    void cautaMembru();
    void creaza();

private:

private:
    QSqlDatabase *m_db;

    QVBoxLayout *m_layoutPrincipal;

    QFormLayout *m_layoutForm;
    QLineEdit *m_lineEditNP;
    QLineEdit *m_lineEditNume;

    QHBoxLayout *m_layoutSuma;
    QLineEdit *m_lineEditSuma;
    QComboBox *m_comboBoxValuta;

    QPushButton *m_buttonCreaza;
    QPushButton *m_buttonInapoi;

    std::vector<std::pair<QString, QString>> m_membrii;
    bool m_membruGasit;

    QString m_data;
    QString m_inserator;
    int m_seria;
    QString m_table;
};

#endif // ADAUGAREFEREASTRA_H
