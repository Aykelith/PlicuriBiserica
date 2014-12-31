#include "LunaFereastra.hpp"
#include "SelectareLunaFereastra.hpp"
#include "TabelFereastra.hpp"

LunaFereastra::LunaFereastra(QString data, QSqlDatabase *db, QWidget *parent)
: QWidget(parent)
, m_db (db)
, m_data (data)
{
    this->setStyleSheet("font-size: 10pt; padding:10px; padding-left: 50px; padding-right:50px;");

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

    m_buttonZiNoua = new QPushButton("Zi noua");
    connect(m_buttonZiNoua, SIGNAL(clicked()), this, SLOT(ziNoua()));

    m_buttonVizualizare = new QPushButton("Vizualizare");
    connect(m_buttonVizualizare, SIGNAL(clicked()), this, SLOT(vizualizare()));

    m_buttonStatut = new QPushButton("Statut");

    m_buttonInapoi = new QPushButton("Inapoi");
    connect(m_buttonInapoi, SIGNAL(clicked()), this, SLOT(close()));

    m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addWidget(m_buttonZiNoua);
    m_layoutPrincipal->addWidget(m_buttonVizualizare);
    m_layoutPrincipal->addWidget(m_buttonStatut);
    m_layoutPrincipal->addWidget(m_buttonInapoi);

    this->setLayout(m_layoutPrincipal);
}

void LunaFereastra::closeEvent(QCloseEvent *event)
{
    m_fereastraSelectareLuna = new SelectareLunaFereastra(m_db);
    m_fereastraSelectareLuna->show();
    event->accept();
}

void LunaFereastra::ziNoua()
{
    QString data = QInputDialog::getText(this, "Data", "Introduce-ti data:", QLineEdit::Normal, QDate::currentDate().toString("dd/MM/yyyy"));
    if (data == "") return;

    m_fereastraTabel = new TabelFereastra(m_db, data, true);
    m_fereastraTabel->show();
}

void LunaFereastra::vizualizare()
{
    m_fereastraTabel = new TabelFereastra(m_db, m_data, false);
    m_fereastraTabel->show();
}
