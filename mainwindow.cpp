#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QSqlQueryModel"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("localhost");
    db.setDatabaseName("XE");

    model = new QSqlQueryModel();
    trzymacz = new QSqlQuery();

}

void MainWindow::refreshStatus()
{
    trzymacz->exec();
    model->setQuery(*trzymacz);
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    db.setUserName(ui->lineEdit->text());
    db.setPassword(ui->lineEdit_2->text());

    if(!db.open())
    {
        ui->statusBar->showMessage("Nieudane polaczenie z baza danych");
    }
    else
    {
        ui->statusBar->showMessage("Udane polaczenie z baza danych");
    }

        trzymacz->prepare("SELECT NRDZIENNIKA as Lp, IMIE as Imię, NAZWISKO FROM UCZNIOWIE");
        refreshStatus();
}

void MainWindow::on_actionLista_Pracownik_w_triggered()
{
    trzymacz->prepare("select IMIE, NAZWISKO, STANOWISKAM.TYTUL as Stanowisko FROM NAUCZYCIELE INNER JOIN STANOWISKAM ON STANOWISKAM.ID_STANOWISKA = NAUCZYCIELE.ID_STANOWISKA");
    refreshStatus();
}

void MainWindow::on_actionLista_Uczni_w_triggered()
{
    trzymacz->prepare("SELECT IMIE , NAZWISKO FROM UCZNIOWIE");
    refreshStatus();
    model->setHeaderData(0,Qt::Horizontal,tr("Imię"));
    model->setHeaderData(1,Qt::Horizontal,tr("Nazwisko"));
}
