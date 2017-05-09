#include "querybank.h"

QueryBank::QueryBank()
{

}

void QueryBank::QUczniowie(QSqlQuery *q, QSqlQueryModel *m)
{
    q->prepare("select * from UCZNIOWIE");
    //q->prepare("select IMIE, NAZWISKO, DATA_URODZENIA, MIASTO, \
               ULICA, KOD_POCZTOWY, IMIE_MATKI, TELEFON_MATKI, \
                IMIE_OJCA, TELEFON_OJCA, GRUPY.NAZWA_GRUPY from UCZNIOWIE inner join GRUPY on\
                UCZNIOWIE.ID_GRUPY = GRUPY.ID_GRUPY ");

    q->exec();
    m->setQuery(*q);

    // Podpisywanie kolumn
    m->setHeaderData(0,Qt::Horizontal,("Imię"));
    m->setHeaderData(1,Qt::Horizontal,("Nazwisko"));
    m->setHeaderData(2,Qt::Horizontal,("Data urodzenia"));
    m->setHeaderData(3,Qt::Horizontal,("Miasto"));
    m->setHeaderData(4,Qt::Horizontal,("Ulica"));
    m->setHeaderData(5,Qt::Horizontal,("Kod pocztowy"));
    m->setHeaderData(6,Qt::Horizontal,("Imię Matki"));
    m->setHeaderData(7,Qt::Horizontal,("Tel. do matki"));
    m->setHeaderData(8,Qt::Horizontal,("Imię Ojca"));
    m->setHeaderData(9,Qt::Horizontal,("Tel. do ojca"));
    m->setHeaderData(10,Qt::Horizontal,("Klasa"));
}

void QueryBank::QUczniowieGrupy(QSqlQuery *q, QSqlQueryModel *m, QString &kl)
{

    q->prepare("select IMIE,NAZWISKO, GRUPY.NAZWA_GRUPY from UCZNIOWIE inner join GRUPY on UCZNIOWIE.ID_GRUPY = GRUPY.ID_GRUPY\
             where GRUPY.NAZWA_GRUPY like ? ");

    q->addBindValue(kl);
    q->exec();
    m->setQuery(*q);

    m->setHeaderData(0,Qt::Horizontal,("Imię"));
    m->setHeaderData(1,Qt::Horizontal,("Nazwisko"));
    m->setHeaderData(2,Qt::Horizontal,("Klasa"));
}
