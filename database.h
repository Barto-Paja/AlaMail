#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

#include "mainwindow.h"

class DataBase
{
    class MainWindow;
public:
    DataBase();

    QSqlDatabase db;

    void login();
};

#endif // DATABASE_H
