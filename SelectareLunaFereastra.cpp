#include "SelectareLunaFereastra.hpp"
#include "LunaFereastra.hpp"

SelectareLunaFereastra::SelectareLunaFereastra(QSqlDatabase *db, QWidget *parent)
: QWidget(parent)
, m_db (db)
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
                        "QComboBox { font-size: 10pt; padding:10px; }");

    m_comboBoxAn = new QComboBox();
    construiesteAnii();
    connect(m_comboBoxAn, SIGNAL(currentIndexChanged(QString)), this, SLOT(construiesteLunile(QString)));

    m_comboBoxLuna = new QComboBox();

    if (m_comboBoxAn->count() != 0)
        construiesteLunile(m_comboBoxAn->currentText());

    m_buttonVizualizareLuna = new QPushButton("Vizualizare luna");
    connect(m_buttonVizualizareLuna, SIGNAL(clicked()), this, SLOT(vizualizareLuna()));

    m_buttonVizualizareAn = new QPushButton("Vizualizare an");

    m_buttonIesire = new QPushButton("Iesire");
    connect(m_buttonIesire, SIGNAL(clicked()), this, SLOT(close()));

    verificAnNou();

    m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addWidget(m_comboBoxAn);
    m_layoutPrincipal->addWidget(m_comboBoxLuna);
    m_layoutPrincipal->addWidget(m_buttonVizualizareLuna);
    m_layoutPrincipal->addWidget(m_buttonVizualizareAn);
    m_layoutPrincipal->addWidget(m_buttonIesire);

    this->setLayout(m_layoutPrincipal);
}

void SelectareLunaFereastra::vizualizareLuna()
{
    QString data = QString::number(m_comboBoxLuna->currentIndex()+1);
    if (data.size() == 1) data.push_front("0");
    data += "/" + m_comboBoxAn->currentText();
    m_fereastraLuna = new LunaFereastra(data, m_db);
    m_fereastraLuna->show();
    this->close();
}

void SelectareLunaFereastra::construiesteLunile(QString anul)
{
    m_comboBoxLuna->clear();

    int lastMonth = 12;
    if (anul.toInt() == QDate::currentDate().year())
    {
        lastMonth = QDate::currentDate().month();
    }

    for (int i=1; i <= lastMonth; ++i)
    {
        m_comboBoxLuna->addItem(getMonth(i));
    }

    m_comboBoxLuna->setCurrentIndex(m_comboBoxLuna->count()-1);
}


void SelectareLunaFereastra::verificAnNou()
{
    QStringList tabeleDatabase = m_db->tables();

    if (!tabeleDatabase.contains("t"+QString::number(QDate::currentDate().year())))
    {
        QSqlQuery query(*m_db);
        query.exec("CREATE TABLE `t" + QString::number(QDate::currentDate().year()) + "` ( \
                   `ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
                   `NP`	VARCHAR NOT NULL, \
                   `Nume`	VARCHAR NOT NULL, \
                   `Suma`	VARCHAR NOT NULL, \
                   `Data`	VARCHAR NOT NULL, \
                   `Inserator`	VARCHAR NOT NULL, \
                   `Seria`	INTEGER NOT NULL \
               );");

        if (query.lastError().number() == -1)
        {
            m_comboBoxAn->addItem(QString::number(QDate::currentDate().year()));
            m_comboBoxAn->setCurrentIndex(m_comboBoxAn->count()-1);
        }
        else
        {
            qDebug() << query.lastError();
        }
    }
}

void SelectareLunaFereastra::construiesteAnii()
{
    QStringList tabeleDatabase = m_db->tables();

    qDebug() << tabeleDatabase;

    for (int i=0; i<tabeleDatabase.size(); ++i)
    {
        if (tabeleDatabase[i].at(0) == 't')
        {
            m_comboBoxAn->addItem(tabeleDatabase[i].right(4));
        }
    }
}

QString SelectareLunaFereastra::getMonth(int number)
{
    switch (number) {
        case 1:
            return "Ianuarie";
            break;
        case 2:
            return "Februarie";
            break;
        case 3:
            return "Martie";
            break;
        case 4:
            return "Aprilie";
            break;
        case 5:
            return "Mai";
            break;
        case 6:
            return "Iunie";
            break;
        case 7:
            return "Iulie";
            break;
        case 8:
            return "August";
            break;
        case 9:
            return "Septembrie";
            break;
        case 10:
            return "Octombrie";
            break;
        case 11:
            return "Noiembrie";
            break;
        case 12:
            return "Decembrie";
            break;
        default:
            return "Eroare";
    }
}
