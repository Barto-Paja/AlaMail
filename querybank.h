#ifndef QUERYBANK_H
#define QUERYBANK_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

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
   QString getLogin() const;

   bool isUserExist(QString nLogin);
   void updateUser(QString pEmail, QString pLogin, QString pName, QString pSurname);

   void closeDB();

   void setQModel(QSqlQueryModel& qmodel);

   void loadMyClass();

private:
    QSqlDatabase db;
    QSqlQuery *query;
//    QSqlRecord record;
//    QSqlQueryModel q_model;
//    QSqlTableModel *t_model;

    static QString vLogin;
};

#endif // QUERYBANK_H
