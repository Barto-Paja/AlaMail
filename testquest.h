#ifndef TESTQUEST_H
#define TESTQUEST_H

#include <QSqlQueryModel>
#include <QSqlQuery>

class testquest
{
public:
    testquest();

    QSqlQuery* quest;
    void testQuery(QSqlQueryModel* m, QSqlQuery* q);
};

#endif // TESTQUEST_H
