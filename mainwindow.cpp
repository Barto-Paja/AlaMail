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
    db.setUserName("******");
    db.setPassword("******");

    if(db.open())
    {
        ui->statusBar->showMessage("Połączono z bazą pomyślnie");
    }

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery q(db);

    q.prepare("SELECT * FROM USERS_ALAMAIL WHERE USERNAME ='"+ui->lineEdit->text()+"' AND PASSWORD='"+ui->lineEdit_2->text()+"'");
    q.exec();

    if(q.next())
    {
       ui->statusBar->showMessage("Zalogowano!");
    }
    else
    {
        ui->statusBar->showMessage("Niepoprawny login lub hasło");
    }
}
