#ifndef QUERYBANK_H
#define QUERYBANK_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class QueryBank
{
public:

   QueryBank();
    ~QueryBank();

   bool isOpen();
   bool Login(QString &login, QString &password);
   QString userInfo(int value);

   void setLogin(QString login);
   QString getLogin();

   void closeDB();

private:
    QSqlDatabase db;
    QSqlQuery *query;

    QString vLogin;
};

#endif // QUERYBANK_H
