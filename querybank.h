#ifndef QUERYBANK_H
#define QUERYBANK_H

#include <QSqlQuery>
#include <QSqlQueryModel>


class QueryBank
{
public:
    QueryBank();

    void QUczniowie(QSqlQuery *q, QSqlQueryModel *m);
    void QUczniowieGrupy(QSqlQuery *q, QSqlQueryModel *m, QString &kl);
};

#endif // QUERYBANK_H
