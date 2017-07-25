#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wskQb = new QueryBank;

    if(wskQb->isOpen())
        ui->statusBar->showMessage("Połączono z bazą danych");
    else
        ui->statusBar->showMessage("Nie połączono z bazą danych");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lE_Login->text();
    QString pass = ui->lE_Password->text();

    wskQb->setLogin(login);

    if(wskQb->Login(login,pass))
    {
        ui->statusBar->showMessage("Zalogowano pomyślnie!");

        ui->statusBar->showMessage(wskQb->getLogin());
        ui->lLogin->setText(wskQb->userInfo(4));

        ui->Profile->setEnabled(true);
    }

}

void MainWindow::on_Profile_clicked()
{
    wskQb->closeDB();
    form = new Profile(0,ui->lE_Login->text());
    form->show();
}
