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

#include "f_dodajucznia.h"
#include "mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public QueryBank
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QSqlDatabase db;
    QSqlQuery *q;
    QSqlQueryModel *m;

    F_DodajUcznia *form;

    void setQ(QSqlQuery *Q);

    ~MainWindow();
public slots:
    void odbiorF_DU(QSqlQuery);

private slots:

    void on_pushButton_clicked();

    void on_actionKompletna_Lista_Uczni_w_triggered();
    void on_actionPodgl_d_Klasy_triggered();
    void on_actionDodaj_ucznia_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
