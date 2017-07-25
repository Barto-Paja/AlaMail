#include "querybank.h"

#include <QMessageBox>

QueryBank::QueryBank()
{

}

QueryBank::~QueryBank()
{
    query->clear();
    delete query;
    db.close();
    db = QSqlDatabase();
    db.removeDatabase("db");
}

bool QueryBank::isOpen()
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QOCI","db");
        //db = QSqlDatabase::database("db");
        db.setHostName("localhost");
        db.setDatabaseName("XE");
        db.setUserName("******");
        db.setPassword("******");
    }

    query = new QSqlQuery(db);

    if(db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool QueryBank::Login(QString& login, QString& password)
{

    if(db.isOpen()) {
        query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME ='"+login+"' AND PASSWORD='"+password+"'");
        query->exec();
        if(query->next())
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
      return false;
}

QString QueryBank::userInfo(int value)
{

    if(db.isOpen()){

    query->prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME = '"+vLogin+"'");
    query->exec();
    if(query->next())
    {
        QString result = query->value(value).toString();
        return result;
    }

    }
}

void QueryBank::setLogin(QString login)
{
    vLogin = login;
}

QString QueryBank::getLogin()
{
    return vLogin;
}

void QueryBank::closeDB()
{
    query->clear();
    delete query;
    db.close();
    db = QSqlDatabase();
    db.removeDatabase("db");
}



