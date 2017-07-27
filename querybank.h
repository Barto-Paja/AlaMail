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
   bool isUserExist(QString nLogin);

   void updateUser();

   void closeDB();

private:
    QSqlDatabase db;
    QSqlQuery *query;

    static QString vLogin;
};

#endif // QUERYBANK_H
