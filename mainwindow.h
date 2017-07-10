#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

#include <QMessageBox>
#include <QInputDialog>

#include "querybank.h"

#include "mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public QueryBank
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:

private slots:


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

};

#endif // MAINWINDOW_H
