#include "f_dodajucznia.h"
#include "ui_f_dodajucznia.h"

F_DodajUcznia::F_DodajUcznia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::F_DodajUcznia)
{
    ui->setupUi(this);

    qr = new QSqlQuery();
    mdl = new QSqlQueryModel();
}

F_DodajUcznia::~F_DodajUcznia()
{
    delete ui;
}

void F_DodajUcznia::on_pushButton_clicked()
{
    czyPelne();
}

void F_DodajUcznia::czyPelne()
{
    QMessageBox msgBox;

    if(ui->lineEdit->text().isEmpty())
    {
        msgBox.setText("Wpisz imię ucznia!");
        msgBox.exec();
    }
    else if(ui->lineEdit_2->text().isEmpty())
    {
        msgBox.setText("Wpisz nazwisko ucznia!");
        msgBox.exec();
    }
    else if(ui->lineEdit_3->text().isEmpty())
    {
        msgBox.setText("Podaj datę urodzenia ucznia!");
        msgBox.exec();
    }
    else if(ui->lineEdit_4->text().isEmpty())
    {
        msgBox.setText("Wpisz miasto!");
        msgBox.exec();
    }
    else if(ui->lineEdit_5->text().isEmpty())
    {
        msgBox.setText("Podaj ulice lub numer domu!");
        msgBox.exec();
    }
    else if(ui->lineEdit_6->text().isEmpty())
    {
        msgBox.setText("Podaj kod pocztowy!");
        msgBox.exec();
    }
    else if(ui->lineEdit_7->text().isEmpty())
    {
        msgBox.setText("Wpisz imię matki!");
        msgBox.exec();
    }
    else if(ui->lineEdit_8->text().isEmpty())
    {
        msgBox.setText("Wpisz imię ojca!");
        msgBox.exec();
    }
    else if(ui->lineEdit_9->text().isEmpty())
    {
        msgBox.setText("Wpisz numer telefonu!");
        msgBox.exec();
    }
    else if(ui->lineEdit_10->text().isEmpty())
    {
        msgBox.setText("Wpisz numer telefonu ojca!");
        msgBox.exec();
    }
    else {
        QSqlQuery q;
        q.prepare("insert into UCZNIOWIE (IMIE,NAZWISKO,DATA_URODZENIA,MIASTO,ULICA,KOD_POCZTOWY,IMIE_MATKI,TELEFON_MATKI,IMIE_OJCA,TELEFON_OJCA,ID_GRUPY) values\
(?,?,?,?,?,?,?,?,?,?)");
        q.addBindValue(QString(ui->lineEdit->text()));
        q.addBindValue(QString(ui->lineEdit_2->text()));
        q.addBindValue(QString(ui->lineEdit_3->text()));
        q.addBindValue(QString(ui->lineEdit_4->text()));
        q.addBindValue(QString(ui->lineEdit_5->text()));
        q.addBindValue(QString(ui->lineEdit_6->text()));
        q.addBindValue(QString(ui->lineEdit_7->text()));
        q.addBindValue(QString(ui->lineEdit_8->text()));
        q.addBindValue(QString(ui->lineEdit_9->text()));
        q.addBindValue(QString(ui->lineEdit_10->text()));

        emit send(q);
    }
}
