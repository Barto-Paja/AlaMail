#include "f_dodajucznia.h"
#include "ui_f_dodajucznia.h"

#include <QSqlError>

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

      QSqlDatabase db = QSqlDatabase::database();
      if(db.open())
      {
          QSqlQuery q(db);

          q.prepare("insert into UCZNIOWIE values(:id, :imie, :nazwisko, :miasto, :ulica, :kp, :imM, :telM, :imO, :telO, :idg)");
          q.bindValue(":id",' ');
          q.bindValue(":imie",QString(ui->lineEdit->text()));
          q.bindValue(":nazwisko",QString(ui->lineEdit_2->text()));
          q.bindValue(":miasto",QString(ui->lineEdit_4->text()));
          q.bindValue(":ulica",QString(ui->lineEdit_5->text()));
          q.bindValue(":kp",QString(ui->lineEdit_6->text()));
          q.bindValue(":imM",QString(ui->lineEdit_7->text()));
          q.bindValue(":telM",QString(ui->lineEdit_8->text()));
          q.bindValue(":imO",QString(ui->lineEdit_9->text()));
          q.bindValue(":telO",QString(ui->lineEdit_10->text()));
          q.bindValue(":idg",1);

          q.exec();
          if(q.lastError().type() != QSqlError::NoError)
          {
          msgBox.setIcon(QMessageBox::Information);
          msgBox.setText(q.lastError().text());
          msgBox.exec();
          }
          else
          {
              msgBox.setText("Dodano nowego Ucznia");
              msgBox.exec();
          }
      }
      else
      {
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.setText("Nieudane połączenie z bazą danych");
          msgBox.exec();
      }

    }
}
