#include "TabelFereastra.hpp"

TabelFereastra::TabelFereastra(QSqlDatabase *db, QString data, bool editabil, QWidget *parent)
: QDialog(parent)
, m_db (db)
, m_data (data)
, m_cautareInitiala ("")
, m_restrictionareData (false)
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

    this->setStyleSheet("QPushButton { font-size: 10pt; padding:10px; padding-left: 50px; padding-right:50px;}"
                        "QComboBox { font-size: 10pt; padding:10px; }"
                        "QLabel { font-size: 10pt; padding-top:10px; padding-bottom:10px; }"
                        "QLineEdit { font-size: 10pt; padding-top:10px; padding-bottom:10px; }");
    this->setModal(true);

    if (editabil)
    {
        QSqlQuery query(*m_db);
        query.exec("SELECT Seria FROM t" + data.right(4) + " WHERE Data='" + data + "' ORDER BY Seria DESC LIMIT 1");
        qDebug() << query.lastError();
        if (query.next())
        {
            m_seria = query.value("Seria").toInt() + 1;
        }
        else
        {
            m_seria = 1;
        }
        qDebug() << m_seria;
    }

    m_buttonAdauga = new QPushButton("Adauga");
    m_buttonAdauga->setEnabled(false);
    connect(m_buttonAdauga, SIGNAL(clicked()), this, SLOT(adaugare()));

    m_buttonPrinteaza = new QPushButton("Printeaza");
    connect(m_buttonPrinteaza, SIGNAL(clicked()), this, SLOT(printeaza()));

    m_lineEditCauta = new QLineEdit();

    m_comboBoxCauta = new QComboBox();
    m_comboBoxCauta->addItem("NP");
    m_comboBoxCauta->addItem("Nume");
    m_comboBoxCauta->addItem("Suma");
    m_comboBoxCauta->addItem("Data");
    m_comboBoxCauta->addItem("Inserator");

    m_buttonCauta = new QPushButton("Cauta");
    connect(m_buttonCauta, SIGNAL(clicked()), this, SLOT(cauta()));

    m_layoutCauta = new QHBoxLayout();
    m_layoutCauta->addWidget(m_lineEditCauta);
    m_layoutCauta->addWidget(m_comboBoxCauta);
    m_layoutCauta->addWidget(m_buttonCauta);

    if (editabil)
    {
        m_labelInserator = new QLabel("Inserator:");
        m_lineEditInserator = new QLineEdit();
        connect(m_lineEditInserator, SIGNAL(textChanged(QString)), this, SLOT(verificaInserator(QString)));

        m_layoutInserator = new QHBoxLayout();
        m_layoutInserator->addWidget(m_labelInserator);
        m_layoutInserator->addWidget(m_lineEditInserator);
    }
    else
    {
        m_buttonPrinteaza->setEnabled(false);
    }

    m_buttonInapoi = new QPushButton("Inapoi");
    connect(m_buttonInapoi, SIGNAL(clicked()), this, SLOT(close()));

    m_layoutOptiuni = new QHBoxLayout();
    m_layoutOptiuni->addWidget(m_buttonAdauga);
    m_layoutOptiuni->addWidget(m_buttonPrinteaza);
    m_layoutOptiuni->addWidget(m_buttonInapoi);

    m_numeTabel = "t" + m_data.right(4);

    if (m_data.size() > 4)
    {
        m_cautareInitiala = " WHERE Data LIKE '%" + m_data + "%'";
        m_restrictionareData = true;

        if (editabil) m_cautareInitiala += " AND Seria=" + QString::number(m_seria);
    }

    m_tabelModel = new QSqlQueryModel();
    m_tabel = new QTableView();
    seteazaQuery(m_cautareInitiala);

    m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addLayout(m_layoutOptiuni);
    m_layoutPrincipal->addLayout(m_layoutCauta);
    if (editabil) m_layoutPrincipal->addLayout(m_layoutInserator);
    m_layoutPrincipal->addWidget(m_tabel);

    this->setLayout(m_layoutPrincipal);
}

void TabelFereastra::adaugare()
{
    m_fereastraAdaugare = new AdaugareFereastra(m_data, m_lineEditInserator->text(), m_seria, m_db, this);
    m_fereastraAdaugare->show();
    connect(m_fereastraAdaugare, SIGNAL(finished(int)), this, SLOT(adaugareTerminata(int)));
}

void TabelFereastra::printeaza()
{
    m_data.replace("/", "-");
    std::ofstream file("rapoarte/Raport " + m_data.toStdString() + " " + QString::number(m_seria).toStdString() + ".html");
    file << "<html><head><style>table, td {border: 1px solid black;	border-collapse: collapse;}</style></head><body>Nume numarator: " << m_lineEditInserator->text().toStdString() << "<br/><table>";

    int totalLEI = 0;
    int totalEURO = 0;
    int totalDOLARI = 0;

    file << "<tr><td>Nr.</td><td>Nr. plic</td><td>Nume</td><td>Suma</td><td style='width:100px'>Semnatura</td>";
    for (int i=0; i<m_tabelModel->rowCount(); ++i)
    {
        file << "<tr><td>" << i << "</td>";
        for (int j=1; j<=3; ++j)
        {
            file << "<td>" << m_tabelModel->data(m_tabelModel->index(i,j)).toString().toStdString() << "</td>";
        }
        QString sumaString = m_tabelModel->data(m_tabelModel->index(i,3)).toString();
        int sumaInt = sumaString.left(sumaString.indexOf(" ")).toInt();
        if (sumaString.right(2) == "EI") totalLEI += sumaInt;
        else if (sumaString.right(2) == "RO") totalEURO += sumaInt;
        else totalDOLARI += sumaInt;

        file << "<td>&nbsp;</td></tr>";
    }

    file << "</table><br/>Total suma: ";
    if (totalLEI != 0) file << totalLEI << " LEI";
    if (totalEURO != 0)
    {
        if (totalLEI != 0) file << ", ";
        file << totalEURO << " EURO";
    }
    if (totalDOLARI != 0)
    {
        if (totalEURO != 0 || totalLEI != 0) file << ", ";
        file << totalDOLARI << " DOLARI";
    }

    file << "<br/><br/>Semnatura casier: ________________________<br/></body></html>";

    file.close();

    QMessageBox::information(this,"Raport printat","Raportul 'Raport " + m_data + " " + QString::number(m_seria) + ".html' a fost generat.");
}

void TabelFereastra::cauta()
{
    if (m_lineEditCauta->text() != "")
    {
        QString query = " WHERE " + m_comboBoxCauta->currentText() + " LIKE '%" + m_lineEditCauta->text() + "%'";
        if (m_restrictionareData)
        {
            query += " AND " + m_cautareInitiala.right(m_cautareInitiala.size()-7);
        }
        seteazaQuery(query);
    }
    else
    {
        seteazaQuery(m_cautareInitiala);
    }
}

void TabelFereastra::adaugareTerminata(int result)
{
    seteazaQuery(m_cautareInitiala);
}

void TabelFereastra::verificaInserator(QString text)
{
    m_buttonAdauga->setEnabled(!text.isEmpty());
}

void TabelFereastra::seteazaQuery(QString queryAditional)
{
    m_tabelModel->setQuery("SELECT ID,NP,Nume,Suma,Data,Inserator FROM " + m_numeTabel + queryAditional, *m_db);

    m_tabel->setModel(m_tabelModel);
    m_tabel->hideColumn(0);
}
