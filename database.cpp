#include "database.h"

DataBase::DataBase()
{

}

void DataBase::login()
{
    db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("localhost");
    db.setDatabaseName("XE");
    db.setUserName("system");
    db.setPassword("SYSTEM");

    if(db.open())
    {
        MainWindow status();

    }
}
