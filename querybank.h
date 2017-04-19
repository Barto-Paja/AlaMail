#ifndef QUERYBANK_H
#define QUERYBANK_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class QueryBank
{
public:
    QueryBank();

    void QUczniowie(QSqlQuery *q, QSqlQueryModel *m);
};

#endif // QUERYBANK_H
