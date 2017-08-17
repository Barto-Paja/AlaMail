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

        ui->Profile->setEnabled(true);
        ui->My_class->setEnabled(true);
        ui->Timetable->setEnabled(true);

        if(wskQb->isAdmin())
        {
            ui->label_2->setText("Administrator");
        }
        else if(wskQb->isModer())
        {
            ui->label_2->setText("Moderator");
        }
        else if(wskQb->isBanned())
        {
            QMessageBox::information(0,"Konto","Konto prewencyjnie zablokowane! \n Skontaktuj się z Moderatorem Bazy lub Administratorem Bazy w celu wyjaśnienia i odblokowania");
            ui->label_2->setText("<font color='red'> Zablokowane!</font>");
            ui->Profile->setEnabled(false);
            ui->My_class->setEnabled(false);
            ui->Timetable->setEnabled(false);
            //wskQb->closeDB();
        }
        else
        {
            ui->label_2->setText("Użytkownik");

        }
    }
    else
    {
        ui->statusBar->showMessage("Niepoprawny login lub hasło");
    }

}

void MainWindow::on_Profile_clicked()
{
    wskQb->closeDB();
    form = new Profile();
    form->show();
}

void MainWindow::on_My_class_clicked()
{
    wskQb->closeDB();
    form2 = new MyClassWin();
    form2->show();
}
