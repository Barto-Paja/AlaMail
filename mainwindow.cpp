#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("localhost");
    db.setDatabaseName("XE");

    q = new QSqlQuery(db);
    m = new QSqlQueryModel();

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
       ui->statusBar->showMessage("Nieudana próba otwarcia bazy danych");
   }
   else
   {
       ui->statusBar->showMessage("Połączenie pomyślne");
   }
   db.close();
}


void MainWindow::on_actionKompletna_Lista_Uczni_w_triggered()
{
    if(db.open())
    {
    q->prepare("select IMIE, NAZWISKO, DATA_URODZENIA, MIASTO, \
ULICA, KOD_POCZTOWY, IMIE_MATKI, TELEFON_MATKI, IMIE_OJCA, TELEFON_OJCA, ID_GRUPY from UCZNIOWIE");
    q->exec();
    m->setQuery(*q);
    ui->tableView->setModel(m);
    db.close();
    }
    else
    {
        ui->statusBar->showMessage("Nieudane połączenie");
    }
}
