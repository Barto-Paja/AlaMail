#include "podglad.h"
#include "ui_podglad.h"

Podglad::Podglad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Podglad)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *trzymacz = new QSqlQuery();

    trzymacz->prepare("SELECT  NRDZIENNIKA as Lp, IMIE as Imię, NAZWISKO, FROM UCZNIOWIE");
    trzymacz->exec();

    model->setQuery(*trzymacz);
    ui->tableView->setModel(model);

}

Podglad::~Podglad()
{
    delete ui;
}
