#include "AdaugareFereastra.hpp"

AdaugareFereastra::AdaugareFereastra(QString data, QString inserator, int seria, QSqlDatabase *db, QWidget *parent)
: QDialog(parent)
, m_db (db)
, m_membruGasit (false)
, m_data (data)
, m_inserator (inserator)
, m_seria (seria)
{
    // Incerc sa ma conected la baza de date
    if (!m_db || !m_db->isOpen())
    {
        m_db = new QSqlDatabase();
        if (!connectDatabase(*m_db))
        {
            showError("Eroare fisiere", "100: Anumite fisiere au nu pot fi gasite!");
            exit(0);
        }
    }

    this->setModal(true);

    m_table = "t" + m_data.right(4);

    QSqlQuery query(*m_db);
    query.exec("SELECT * FROM Membrii");

    while (query.next())
    {
        m_membrii.push_back(std::pair<QString,QString>(query.value("NP").toString(), query.value("Nume").toString()));
    }

    m_lineEditNP = new QLineEdit();
    connect(m_lineEditNP, SIGNAL(editingFinished()), this, SLOT(cautaMembru()));

    m_lineEditNume = new QLineEdit();

    m_lineEditSuma = new QLineEdit();

    m_comboBoxValuta = new QComboBox();
    m_comboBoxValuta->addItem("LEI");
    m_comboBoxValuta->addItem("EURO");
    m_comboBoxValuta->addItem("DOLARI");

    m_layoutSuma = new QHBoxLayout();
    m_layoutSuma->addWidget(m_lineEditSuma);
    m_layoutSuma->addWidget(m_comboBoxValuta);

    m_layoutForm = new QFormLayout();
    m_layoutForm->addRow("Numar plic:", m_lineEditNP);
    m_layoutForm->addRow("Nume:", m_lineEditNume);
    m_layoutForm->addRow("Suma:", m_layoutSuma);

    m_buttonCreaza = new QPushButton("Creaza");
    connect(m_buttonCreaza, SIGNAL(clicked()), this, SLOT(creaza()));

    m_buttonInapoi = new QPushButton("Inapoi");
    connect(m_buttonInapoi, SIGNAL(clicked()), this, SLOT(close()));

    m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addLayout(m_layoutForm);
    m_layoutPrincipal->addWidget(m_buttonCreaza);
    m_layoutPrincipal->addWidget(m_buttonInapoi);

    this->setLayout(m_layoutPrincipal);
}

void AdaugareFereastra::cautaMembru()
{
    if (m_lineEditNP->text() != "")
    {
        for (std::size_t i=0; i<m_membrii.size(); ++i)
        {
            if (m_membrii[i].first == m_lineEditNP->text())
            {
                m_lineEditNume->setText(m_membrii[i].second);
                m_membruGasit = true;
                break;
            }
        }
    }
    m_membruGasit = false;
}

void AdaugareFereastra::creaza()
{
    if (m_lineEditNP->text() != "" && m_lineEditNume->text() != "" && m_lineEditSuma->text() != "")
    {
        QSqlQuery query(*m_db);
        query.exec("INSERT INTO " + m_table + "(NP, Nume, Suma, Data, Inserator, Seria) VALUES"
                   "('" + m_lineEditNP->text() + "','" + m_lineEditNume->text() + "','" + m_lineEditSuma->text() + " " + m_comboBoxValuta->currentText() + "','" + m_data + "','" + m_inserator + "'," + QString::number(m_seria) + ")");

        if (query.lastError().number() == -1)
        {
            if (!m_membruGasit)
            {

            }

            m_lineEditNP->setText("");
            m_lineEditNP->setFocus(Qt::TabFocusReason);
            m_lineEditNume->setText("");
            m_lineEditSuma->setText("");
        }
        else
        {
            showError(QString::number(query.lastError().number()), query.lastError().text());
            qDebug() << query.lastError() << "INSERT INTO " + m_table + "(NP, Nume, Suma, Data, Inserator, Seria) VALUES"
                                                                        "('" + m_lineEditNP->text() + "','" + m_lineEditNume->text() + "','" + m_lineEditSuma->text() + " " + m_comboBoxValuta->currentText() + "','" + m_data + "','" + m_inserator + "'," + m_seria + ")";
        }
    }
}


