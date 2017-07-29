#include "querybank.h"

#include <QMessageBox>

#include <iostream>

QString QueryBank::vLogin = NULL;

QueryBank::QueryBank()
{

}

QueryBank::~QueryBank()
{
    if(db.isOpen())
    {
        db.close();
        db = QSqlDatabase();
    }
    db.removeDatabase("db");
}

bool QueryBank::isOpen()
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QOCI","db");
        db.setHostName("localhost");
        db.setDatabaseName("XE");
        db.setUserName("system");
        db.setPassword("SYSTEM");
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

QString QueryBank::getLogin() const
{
    return vLogin;
}

bool QueryBank::isUserExist(QString nLogin)
{
    query->prepare("SELECT USERNAME FROM USERS_ALAMAIL WHERE USERNAME = '"+nLogin+"'");
    query->exec();

    if(vLogin==nLogin)
    {
        return false;
    }
    else if(query->next())
    {
        if(query->value(0).toString().isNull())
            return true;
    }
    else
        return false;

}

void QueryBank::updateUser(QString pEmail, QString pLogin, QString pName, QString pSurname)
{
    query->prepare("UPDATE USERS_ALAMAIL SET EMAIL ='"+pEmail+"' WHERE USERNAME ='"+vLogin+"'");
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET NAZWISKO ='"+pName+"' WHERE USERNAME ='"+vLogin+"'");
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET IMIE ='"+pSurname+"' WHERE USERNAME ='"+vLogin+"'");
    query->exec();

    query->prepare("UPDATE USERS_ALAMAIL SET USERNAME ='"+pLogin+"' WHERE USERNAME ='"+vLogin+"'");
    query->exec();

    vLogin = pLogin;
}

void QueryBank::closeDB()
{
    if(db.isOpen())
    {
        db.close();
        db = QSqlDatabase();
    }
    db.removeDatabase("db");
}

void QueryBank::setQModel(QSqlQueryModel& qmodel)
{
    qmodel.setQuery(*query);
}

void QueryBank::loadMyClass()
{
    query->prepare("SELECT NAZWISKO, IMIE, ID_UCZNIA FROM UCZNIOWIE ORDER BY NAZWISKO");
    query->exec();
}



