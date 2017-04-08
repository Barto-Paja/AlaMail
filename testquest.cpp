#include "testquest.h"

testquest::testquest()
{
    quest = new QSqlQuery();
}

void testquest::testQuery(QSqlQueryModel *m, QSqlQuery* q)
{
    q->prepare("select * from NAUCZYCIELE");
    q->exec();
    m->setQuery(*q);
}
