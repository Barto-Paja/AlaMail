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

    form = new F_DodajUcznia(this);

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
        QueryBank::QUczniowie(q,m);
        ui->tableView->setModel(m);
        db.close();
    }
    else
    {
        ui->statusBar->showMessage("Nieudane połączenie");
    }
}

void MainWindow::on_actionPodgl_d_Klasy_triggered()
{
    QString txt = QInputDialog::getText(this,QString("Wybór klasy"),QString("Podaj nazwę klasy:"));

    if(db.open())
    {
        QueryBank::QUczniowieGrupy(q,m, txt);
        ui->tableView->setModel(m);
        db.close();
    }
    else
    {
        ui->statusBar->showMessage("Nieudane połączenie");
    }
}

void MainWindow::on_actionDodaj_ucznia_triggered()
{
    form->setModal(true);
    form->exec();
}
